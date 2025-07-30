import numpy as np
# import cv2

def euler_angles_to_rotation_matrix(roll: float, pitch: float, yaw: float) -> np.ndarray:
    """
    Construct a 3×3 rotation matrix from roll, pitch, yaw (in radians).
    Convention: roll about X, pitch about Y, yaw about Z (intrinsic rotations).
    R = R_z(yaw) @ R_y(pitch) @ R_x(roll).
    """
    cx, sx = np.cos(roll), np.sin(roll)
    cy, sy = np.cos(pitch), np.sin(pitch)
    cz, sz = np.cos(yaw), np.sin(yaw)

    R_x = np.array([
        [1,   0,    0],
        [0,  cx,  -sx],
        [0,  sx,   cx]
    ])

    R_y = np.array([
        [ cy,  0,  sy],
        [  0,  1,   0],
        [-sy,  0,  cy]
    ])

    R_z = np.array([
        [cz,  -sz,  0],
        [sz,   cz,  0],
        [ 0,    0,  1]
    ])

    R = R_z @ R_y @ R_x
    return R


def pixel_to_world(
    pixel: tuple[int, int],
    depth_value: float,
    camera_matrix: np.ndarray,
    dist_coeffs: np.ndarray,
    cam_angle: tuple[float, float, float],
    cam_position: tuple[float, float, float]
) -> np.ndarray:
    """
    Convert a single pixel (u, v) with known depth into its 3D world/vehicle‐frame coordinate.

    Args:
      pixel: (u, v) in image coordinates (integer).
      depth_value: Depth Z at that pixel (float, e.g. meters). Must be > 0.
      camera_matrix: 3×3 intrinsic matrix K = [[fx, 0, cx],
                                               [0, fy, cy],
                                               [0,  0,  1]].
      dist_coeffs: Distortion coefficients (k1, k2, p1, p2, k3), shape (5,) or similar.
      cam_angle: (roll, pitch, yaw) in radians, defining camera orientation in world frame.
      cam_position: (t_x, t_y, t_z) in world coordinates (e.g., meters).

    Returns:
      A numpy array of shape (3,) = [X_world, Y_world, Z_world].
    """
    u, v = pixel
    Z = depth_value

    if Z <= 0 or not np.isfinite(Z):
        raise ValueError("Depth must be positive and finite.")

    pts = np.array([[[float(u), float(v)]]], dtype=np.float32)  # shape (1,1,2)
    # undistorted = cv2.undistortPoints(pts, camera_matrix, dist_coeffs, P=camera_matrix)
    u_ideal = undistorted[0, 0, 0]
    v_ideal = undistorted[0, 0, 1]

    fx = camera_matrix[0, 0]
    fy = camera_matrix[1, 1]
    cx = camera_matrix[0, 2]
    cy = camera_matrix[1, 2]

    x_norm = (u_ideal - cx) / fx
    y_norm = (v_ideal - cy) / fy

    X_cam = x_norm * Z
    Y_cam = y_norm * Z
    Z_cam = Z
    point_cam = np.array([X_cam, Y_cam, Z_cam], dtype=np.float64)

    roll, pitch, yaw = cam_angle
    R_cw = euler_angles_to_rotation_matrix(roll, pitch, yaw)
    t_cw = np.array(cam_position, dtype=np.float64).reshape(3,)

    point_world = R_cw @ point_cam + t_cw

    return point_world
