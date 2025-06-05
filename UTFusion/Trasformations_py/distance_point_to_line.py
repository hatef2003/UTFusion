import numpy as np

def distance_point_to_line(
    point: tuple[float, float, float],
    line_point1: tuple[float, float, float],
    line_point2: tuple[float, float, float]
) -> float:
    """
    Compute the shortest distance from a 3D point to a line defined by two 3D points.

    Args:
      point:       (x, y, z) of the query point P.
      line_point1: (x, y, z) of A on the line.
      line_point2: (x, y, z) of B on the line (must be different from A).

    Returns:
      Shortest distance from point to the infinite line AB.
      Formula: ‖ (B - A) × (A - P ) ‖ / ‖ B - A ‖
    """
    P = np.asarray(point, dtype=float)
    A = np.asarray(line_point1, dtype=float)
    B = np.asarray(line_point2, dtype=float)

    AB = B - A
    if np.allclose(AB, 0):
        raise ValueError("line_point1 and line_point2 must be distinct points.")

    AP = P - A
    cross_prod = np.cross(AB, AP)
    dist = float(np.linalg.norm(cross_prod) / np.linalg.norm(AB))
    return dist
