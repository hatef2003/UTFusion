import numpy as np

def distance(p1: tuple[float, float, float], p2: tuple[float, float, float]) -> float:
    """
    Compute the Euclidean distance between two 3D points.

    Args:
      p1, p2: Each can be array‐like of length 3 (x, y, z).

    Returns:
      Distance (float).
    """
    p1_arr = np.asarray(p1, dtype=float)
    p2_arr = np.asarray(p2, dtype=float)
    return float(np.linalg.norm(p2_arr - p1_arr))
