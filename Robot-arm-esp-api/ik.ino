Vector2f forward_kinematics(float theta1, float theta2, float theta3, float l1, float l2, float l3) {
  float x = l1 * cos(theta1) + l2 * cos(theta1 + theta2) + l3 * cos(theta1 + theta2 + theta3);
  float y = l1 * sin(theta1) + l2 * sin(theta1 + theta2) + l3 * sin(theta1 + theta2 + theta3);
  return Vector2f(x, y);
}

float clip_angle(float angle, float lower_limit, float upper_limit) {
  return fmin(upper_limit, fmax(lower_limit, angle));
}

Vector3f inverse_kinematics(Vector2f target_position, float l1, float l2, float l3, float joint_limit = 90, float tolerance = 1e-1, int max_iterations = 100) {
  float joint_limit_rad = joint_limit * M_PI / 180.0;
  float joint_limit_lower = -joint_limit_rad;
  float joint_limit_upper = joint_limit_rad;

  Vector3f theta = Vector3f::Zero();  // Initial guess for joint angles
  Vector2f end_effector = forward_kinematics(theta(0), theta(1), theta(2), l1, l2, l3);

  for (int iteration = 0; iteration < max_iterations; iteration++) {
    Vector2f error = target_position - end_effector;
    if (error.norm() < tolerance) {
      return theta;
    }

    MatrixXf J{ 2, 3 };
    J << -l1 * sin(theta(0)) - l2 * sin(theta(0) + theta(1)) - l3 * sin(theta(0) + theta(1) + theta(2)),
      -l2 * sin(theta(0) + theta(1)) - l3 * sin(theta(0) + theta(1) + theta(2)),
      -l3 * sin(theta(0) + theta(1) + theta(2)),
      l1 * cos(theta(0)) + l2 * cos(theta(0) + theta(1)) + l3 * cos(theta(0) + theta(1) + theta(2)),
      l2 * cos(theta(0) + theta(1)) + l3 * cos(theta(0) + theta(1) + theta(2)),
      l3 * cos(theta(0) + theta(1) + theta(2));


    // Update joint angles
    MatrixXf J_pinv{ 4, 3 } ;
    J_pinv = J.completeOrthogonalDecomposition().pseudoInverse();

    // Compute delta_theta
    //Vector2f error;
    Matrix<float, 3, 1> delta_theta = J_pinv * error;
    theta += delta_theta;

    // Clip joint angles to the specified limits
    for (int i = 0; i < 3; i++) {
      theta(i) = clip_angle(theta(i), joint_limit_lower, joint_limit_upper);
    }

    // Update end effector position
    end_effector = forward_kinematics(theta(0), theta(1), theta(2), l1, l2, l3);
  }


  return Vector3f::Zero();
}

String calc(float x, float y) {


  float targetX = x;
  float targetY = y;
  float targetX_corrected = 0.0;
  if (targetY <= 0) {
    targetX_corrected = 0.1;
  } else {
    targetX_corrected = targetY;
  }

  float targetY_corrected = targetX;

  Vector2f target_position(targetX_corrected, targetY_corrected);
  Vector3f result = inverse_kinematics(target_position, l1, l2, l3);
  if(result[0] == 0 && result[1] == 0 && result[2] == 0){
    angle1 = "INVALID";
    angle2 = "0.0";
    angle2 = "0.0";
  }
  else{
  angle1 = String(result[0]* 180.0 / M_PI);
  angle2 = String(result[1]* 180.0 / M_PI);
  angle3 = String(result[2]* 180.0 / M_PI);
  }
  String data = "response;"+angle1+";"+angle2+";"+angle3;
  return data;


}
