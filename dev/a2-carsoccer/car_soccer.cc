/** CSci-4611 Assignment 2:  Car Soccer
 */

#include "car_soccer.h"
#include "config.h"


CarSoccer::CarSoccer() : GraphicsApp(1024,768, "Car Soccer") {
    // Define a search path for finding data files (images and shaders)
    searchPath_.push_back(".");
    searchPath_.push_back("./data");
    searchPath_.push_back(DATA_DIR_INSTALL);
    searchPath_.push_back(DATA_DIR_BUILD);
}

CarSoccer::~CarSoccer() {
}


Vector2 CarSoccer::joystick_direction() {
    Vector2 dir;
    if (IsKeyDown(GLFW_KEY_LEFT))
        dir[0]--;
    if (IsKeyDown(GLFW_KEY_RIGHT))
        dir[0]++;
    if (IsKeyDown(GLFW_KEY_UP))
        dir[1]++;
    if (IsKeyDown(GLFW_KEY_DOWN))
        dir[1]--;
    return dir;
}


void CarSoccer::OnSpecialKeyDown(int key, int scancode, int modifiers) {
    if (key == GLFW_KEY_SPACE) {
        // Here's where you could call some form of launch_ball();
        car_.Reset();
        ball_.Reset();


    } 
    if (key == GLFW_KEY_LEFT) {
        car_.left();
      
    }
    if (key == GLFW_KEY_RIGHT) {
        car_.right();
        
    }
    if (key == GLFW_KEY_UP) {
        car_.speed_up();
    }
    if (key == GLFW_KEY_DOWN) {
        car_.slow_down();
    }
}


void CarSoccer::UpdateSimulation(double timeStep) {
    // Here's where you shound do your "simulation", updating the positions of the
    // car and ball as needed and checking for collisions.  Filling this routine
    // in is the main part of the assignment.
    ball_.gravity(timeStep); //update ball's velcity based on gravity's acceleration
    ball_.move(timeStep); //update ball's position
    car_.move(timeStep);

  
    float distance = (ball_.position() - car_.position()).Length();
    if (distance <= (ball_.get_rad() + car_.collision_radius())) { //collision with car
        float distance2 = ball_.get_rad() + car_.collision_radius();
        float difference = distance2 - distance;
        ball_.set_position(ball_.position() + difference * (-ball_.get_velocity().ToUnit()));
        Vector3 normal2 = (ball_.position() - car_.position()).ToUnit(); //normal vector
        Vector3 relative = (ball_.get_velocity() - car_.get_velocity());
        ball_.set_velocity(car_.get_velocity() + relative - (2 * (relative.Dot(normal2))) * normal2); //car velocity incorporated into collision with ball
        ball_.decrease_speed();
    }
    if (car_.get_posx() <= -40) { //ball hits left wall
        Point3 pos_new = Point3(-40.0, car_.get_posy(), car_.get_posz()); //reset position to be touching wall
        car_.set_position(pos_new);
        Vector3 normal2 = Vector3(1, 0, 0); //normal vector
       car_.set_velocity(car_.get_velocity() - (2 * (car_.dot(normal2))) * normal2); //reflection across normal
       
    }
    if (car_.get_posx() >= 40) { //ball hits right wall
        Point3 pos_new = Point3(40.0, car_.get_posy(), car_.get_posz()); //reset position to be touching wall
        car_.set_position(pos_new);
        Vector3 normal2 = Vector3(1, 0, 0); //normal vector
        car_.set_velocity(car_.get_velocity() - (2 * (car_.dot(normal2))) * normal2); //reflection across normal
    }
    if (car_.get_posz() <= -50) { //hits enemy wall
        Point3 pos_new = Point3(car_.get_posx(), car_.get_posy(), -50.0); //reset position to be touching wall
        car_.set_position(pos_new);
        Vector3 normal2 = Vector3(0, 0, 1); //normal vector
        car_.set_velocity(car_.get_velocity() - (2 * (car_.dot(normal2))) * normal2); //reflection across normal
    }
    if (car_.get_posz() >= 50) { //hits home goal
        Point3 pos_new = Point3(car_.get_posx(), car_.get_posy(), 50.0); //reset position to be touching wall
        car_.set_position(pos_new);
        Vector3 normal2 = Vector3(0, 0, 1); //normal vector
        car_.set_velocity(car_.get_velocity() - (2 * (car_.dot(normal2))) * normal2); //reflection across normal
  
    }
    
    if (ball_.get_posy() - ball_.get_rad() <= 0) { //contact with ground or through it
        Point3 pos_new = Point3(ball_.get_posx(), ball_.get_rad(), ball_.get_posz()); //reset position to be touching ground
        ball_.set_position(pos_new);
        Vector3 normal = Vector3(0, 1, 0); //normal vector
        ball_.set_velocity(ball_.get_velocity() - (2 * (ball_.dot(normal)))*normal); //reflection across normal
        ball_.decrease_speed();
    }
    if (ball_.get_posx() <= -40) { //ball hits left wall
        Point3 pos_new = Point3(-40.0, ball_.get_posy(), ball_.get_posz()); //reset position to be touching wall
        ball_.set_position(pos_new);
        Vector3 normal2 = Vector3(1, 0, 0); //normal vector
        ball_.set_velocity(ball_.get_velocity() - (2 * (ball_.dot(normal2))) * normal2); //reflection across normal
        ball_.decrease_speed();
    }
    if (ball_.get_posx() >= 40) { //ball hits right wall
        Point3 pos_new = Point3(40.0, ball_.get_posy(), ball_.get_posz()); //reset position to be touching wall
        ball_.set_position(pos_new);
        Vector3 normal2 = Vector3(1, 0, 0); //normal vector
        ball_.set_velocity(ball_.get_velocity() - (2 * (ball_.dot(normal2))) * normal2); //reflection across normal
        ball_.decrease_speed();
    }
    if (ball_.get_posz() <= -50) { //hits enemy wall
        Point3 pos_new = Point3(ball_.get_posx(), ball_.get_posy(), -50.0); //reset position to be touching wall
        ball_.set_position(pos_new);
        Vector3 normal2 = Vector3(0, 0, 1); //normal vector
        ball_.set_velocity(ball_.get_velocity() - (2 * (ball_.dot(normal2))) * normal2); //reflection across normal
        ball_.decrease_speed();
    }
    if (ball_.get_posz() >= 50) { //hits home goal
        Point3 pos_new = Point3(ball_.get_posx(), ball_.get_posy(), 50.0); //reset position to be touching wall
        ball_.set_position(pos_new);
        Vector3 normal2 = Vector3(0, 0, 1); //normal vector
        ball_.set_velocity(ball_.get_velocity() - (2 * (ball_.dot(normal2))) * normal2); //reflection across normal
        ball_.decrease_speed();
    }
    if (ball_.get_posy() >= 35) { //hits ceiling
        Point3 pos_new = Point3(ball_.get_posx(), 35.0, ball_.get_posz()); //reset position to be touching wall
        ball_.set_position(pos_new);
        Vector3 normal2 = Vector3(0, 1, 0); //normal vector
        ball_.set_velocity(ball_.get_velocity() - (2 * (ball_.dot(normal2))) * normal2); //reflection across normal
        ball_.decrease_speed();

    }

    //goals are hit, reset
    if ((ball_.get_posy() < (20 - ball_.radius())) && (ball_.get_posx() > -10) && (ball_.get_posx() < 10)) {
        if (((ball_.get_posz() - ball_.get_rad()) <= -50) || ((ball_.get_posz() + ball_.get_rad()) >= 50)) {
            ball_.Reset();
            car_.Reset();
        }
    }
}


void CarSoccer::InitOpenGL() {
    // Set up the camera in a good position to see the entire field
    projMatrix_ = Matrix4::Perspective(60, aspect_ratio(), 1, 1000);
    modelMatrix_ = Matrix4::LookAt(Point3(0,60,70), Point3(0,0,10), Vector3(0,1,0));
 
    // Set a background color for the screen
    glClearColor(0.8f, 0.8f, 0.8f, 1.0f);
    
    // Load some image files we'll use
    fieldTex_.InitFromFile(Platform::FindFile("pitch.png", searchPath_));
    crowdTex_.InitFromFile(Platform::FindFile("crowd.png", searchPath_));
}


void CarSoccer::DrawUsingOpenGL() {
    // Draw the crowd as a fullscreen background image
    quickShapes_.DrawFullscreenTexture(Color(1,1,1), crowdTex_);
    
    // Draw the field with the field texture on it.
    Color col(16.0f/255.0f, 46.0f/255.0f, 9.0f/255.0f);
    Matrix4 M = Matrix4::Translation(Vector3(0.0f, -0.201f, 0.0f)) * Matrix4::Scale(Vector3(50.0f, 1.0f, 60.0f));
    quickShapes_.DrawSquare(modelMatrix_ * M, viewMatrix_, projMatrix_, col);
    M = Matrix4::Translation(Vector3(0.0f, -0.2f, 0.0f)) * Matrix4::Scale(Vector3(40.0f, 1.0f, 50.0f));
    quickShapes_.DrawSquare(modelMatrix_ * M, viewMatrix_, projMatrix_, Color(1,1,1), fieldTex_);
    
    // Draw the car
    Color carcol(0.8f, 0.2f, 0.2f);
    Matrix4 Mcar =
        Matrix4::Translation(car_.position() - Point3(0, 0, 0)) *
        Matrix4::Scale(car_.size()) *
        Matrix4::Scale(Vector3(0.5f, 0.5f, 0.5f));
    quickShapes_.DrawCube(modelMatrix_ * Mcar, viewMatrix_, projMatrix_, carcol);
    
    
    // Draw the ball
    Color ballcol(1,1,1);
    Matrix4 Mball =
        Matrix4::Translation(ball_.position() - Point3(0,0,0)) *
        Matrix4::Scale(Vector3(ball_.radius(), ball_.radius(), ball_.radius()));
    quickShapes_.DrawSphere(modelMatrix_ * Mball, viewMatrix_, projMatrix_, ballcol);
    
    
    // Draw the ball's shadow -- this is a bit of a hack, scaling Y by zero
    // flattens the sphere into a pancake, which we then draw just a bit
    // above the ground plane.
    Color shadowcol(0.2f, 0.4f, 0.15f);
    Matrix4 Mshadow =
        Matrix4::Translation(Vector3(ball_.position()[0], -0.1f, ball_.position()[2])) *
        Matrix4::Scale(Vector3(ball_.radius(), 0, ball_.radius())) *
        Matrix4::RotationX(90);
    quickShapes_.DrawSphere(modelMatrix_ * Mshadow, viewMatrix_, projMatrix_, shadowcol);
    
    
    // You should add drawing the goals and the boundary of the playing area
    // using quickShapes_.DrawLines()

    std::vector<Point3> right_lines;
    std::vector<Point3> left_lines;
    std::vector<Point3> up_lines;
    std::vector<Point3> down_lines;
    std::vector<Point3> enemy_bounds;

    right_lines.push_back(Point3(40.0, 0.0, -50.0));
    right_lines.push_back(Point3(40.0, 35.0, -50.0));
    right_lines.push_back(Point3(40.0, 35.0,50.0));
    right_lines.push_back(Point3(40.0, 0.0, 50.0));
    left_lines.push_back(Point3(-40.0, 35.0, 50.0));
    left_lines.push_back(Point3(-40.0, 0.0, 50.0));
    left_lines.push_back(Point3(-40.0, 0.0, -50.0));
    left_lines.push_back(Point3(-40.0, 35.0, -50.0));
    up_lines.push_back(Point3(40.0, 0.0, -50.0));
    up_lines.push_back(Point3(40.0, 35.0, -50.0));
    up_lines.push_back(Point3(-40.0, 35.0, -50.0));
    up_lines.push_back(Point3(-40.0, 0.0, -50.0));
    down_lines.push_back(Point3(40.0, 0.0, 50.0));
    down_lines.push_back(Point3(-40.0, 0.0, 50.0));
    down_lines.push_back(Point3(-40.0, 35.0, 50.0));
    down_lines.push_back(Point3(40.0, 35.0, 50.0));

    quickShapes_.DrawLines(modelMatrix_, viewMatrix_, projMatrix_, Color(255, 255, 255), down_lines, QuickShapes::LinesType::LINE_LOOP, 0.1);
    quickShapes_.DrawLines(modelMatrix_, viewMatrix_, projMatrix_, Color(255, 255, 255), up_lines, QuickShapes::LinesType::LINE_LOOP, 0.1);
    quickShapes_.DrawLines(modelMatrix_, viewMatrix_, projMatrix_, Color(255, 255, 255), left_lines, QuickShapes::LinesType::LINE_LOOP, 0.1);
    quickShapes_.DrawLines(modelMatrix_, viewMatrix_, projMatrix_, Color(255, 255, 255), right_lines, QuickShapes::LinesType::LINE_LOOP, 0.1);
    //frame for enemy goal
    std::vector<Point3> enemy_goal;
    enemy_goal.push_back(Point3(-10.0, 0.0, -50.0));
    enemy_goal.push_back(Point3(10.0, 0.0, -50.0));
    enemy_goal.push_back(Point3(10.0, 10.0, -50.0));
    enemy_goal.push_back(Point3(-10.0, 10.0, -50.0));
    quickShapes_.DrawLines(modelMatrix_, viewMatrix_, projMatrix_, Color(0, 1, 1), enemy_goal, QuickShapes::LinesType::LINE_LOOP, 0.1);

    for (int y = 0; y < 11; y++) {
        quickShapes_.DrawLineSegment(modelMatrix_, viewMatrix_, projMatrix_, Color(0,1,1), Point3(-10, y, -50), Point3(10, y, -50), 0.1);
    }

    for (int x = -10; x < 10; x++) {
        quickShapes_.DrawLineSegment(modelMatrix_, viewMatrix_, projMatrix_, Color(0, 1, 1), Point3(x, 0, -50), Point3(x, 10, -50), 0.1);
    }
    //frame for home goal
    std::vector<Point3> home_goal;
    home_goal.push_back(Point3(-10.0, 0.0, 50.0));
    home_goal.push_back(Point3(10.0, 0.0, 50.0));
    home_goal.push_back(Point3(10.0, 10.0, 50.0));
    home_goal.push_back(Point3(-10.0, 10.0, 50.0));
    quickShapes_.DrawLines(modelMatrix_, viewMatrix_, projMatrix_, Color(0, 1, 1), home_goal, QuickShapes::LinesType::LINE_LOOP, 0.1);

    for (int y = 0; y < 11; y++) {
        quickShapes_.DrawLineSegment(modelMatrix_, viewMatrix_, projMatrix_, Color(0, 1, 1), Point3(-10, y, 50), Point3(10, y, 50), 0.1);
    }

    for (int x = -10; x < 10; x++) {
        quickShapes_.DrawLineSegment(modelMatrix_, viewMatrix_, projMatrix_, Color(0, 1, 1), Point3(x, 0, 50), Point3(x, 10, 50), 0.1);
    }

}
    
