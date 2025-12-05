#pragma once
#include "sprite.hpp"
#include <string>

enum class EnemyState {
    PATROL,
    CHASE,
    RETURN_HOME,
    COOLDOWN
};

class Enemy : public Sprite {
public:
    Enemy(SDL_Renderer* renderer, const std::string& path, int x, int y, int width, int height);

    void update_movement(float dt, int player_x, int player_y);

private:
    // Home point
    int home_x;
    int home_y;

    // Movement direction (2D)
    float dir_x = 0.f;
    float dir_y = 0.f;

    // Patrol
    float patrol_timer = 0.f;

    // Chase
    float chase_timer = 0.f;
    const float max_chase_time = 2.0f;

    // Cooldown after chase
    float cooldown_timer = 0.f;
    const float cooldown_duration = 3.0f;

    // Radius
    const float detection_radius = 200.0f;

    EnemyState state = EnemyState::PATROL;
};
