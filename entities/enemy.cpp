#include "enemy.hpp"

Enemy::Enemy(SDL_Renderer* renderer, const std::string& path, int x, int y, int width, int height)
    : Sprite(renderer, path, x, y, width, height), home_x(x), home_y(y) {}

static float dist(int x1, int y1, int x2, int y2) {
    float dx = static_cast<float>(x1 - x2);
    float dy = static_cast<float>(y1 - y2);
    return std::sqrt(dx*dx + dy*dy);
}

void Enemy::update_movement(float dt, int player_x, int player_y) {
    const float speed = 100.0f;

    float px = (float)player_x;
    float py = (float)player_y;
    float ex = (float)getX();
    float ey = (float)getY();

    float d = dist(ex, ey, px, py);

    // ------------------------
    // CAN WE START CHASING?
    // ------------------------
    if (d < detection_radius &&
        state != EnemyState::CHASE &&
        state != EnemyState::COOLDOWN)
    {
        state = EnemyState::CHASE;
        chase_timer = max_chase_time;
    }

    switch (state) {

    // ================================
    //          CHASE PLAYER
    // ================================
    case EnemyState::CHASE: {
        chase_timer -= dt;

        // Full 2D chase direction
        float dx = px - ex;
        float dy = py - ey;
        float len = std::sqrt(dx*dx + dy*dy);

        if (len > 0.001f) {
            dx /= len;
            dy /= len;
        }

        int new_x = int(ex + dx * speed * 1.8f * dt);
        int new_y = int(ey + dy * speed * 1.8f * dt);

        set_position(new_x, new_y);
        set_animation(dx < 0 ? "left" : "right");

        if (chase_timer <= 0) {
            state = EnemyState::COOLDOWN;
            cooldown_timer = cooldown_duration;
        }
        break;
    }

    // ================================
    //           COOLDOWN
    // ================================
    case EnemyState::COOLDOWN: {
        cooldown_timer -= dt;
        if (cooldown_timer <= 0) {
            state = EnemyState::RETURN_HOME;
        }
        break;
    }

    // ================================
    //    RANDOM FREE 2D PATROL
    // ================================
    case EnemyState::PATROL: {

        patrol_timer -= dt;

        if (patrol_timer <= 0) {
            // Pick a random direction (normalized)
            float angle = (rand() % 628) / 100.0f; // 0–6.28 rad
            dir_x = std::cos(angle);
            dir_y = std::sin(angle);

            patrol_timer = 1.0f + (rand() % 1000) / 1000.0f * 3.0f; // 1–4 seconds
        }

        int new_x = int(ex + dir_x * speed * dt);
        int new_y = int(ey + dir_y * speed * dt);

        set_position(new_x, new_y);
        set_animation(dir_x < 0 ? "left" : "right");

        // Patrol time ended → return home
        if (patrol_timer <= 0) {
            state = EnemyState::RETURN_HOME;
        }
        break;
    }

    // ================================
    //      RETURN TO ORIGIN
    // ================================
    case EnemyState::RETURN_HOME: {
        float dx = home_x - ex;
        float dy = home_y - ey;
        float len = std::sqrt(dx*dx + dy*dy);

        // If reached home
        if (len < 5.0f) {
            set_position(home_x, home_y);
            state = EnemyState::PATROL;
            break;
        }

        dx /= len;
        dy /= len;

        int new_x = int(ex + dx * speed * dt);
        int new_y = int(ey + dy * speed * dt);

        set_position(new_x, new_y);
        set_animation(dx < 0 ? "left" : "right");
        break;
    }
    }
}
