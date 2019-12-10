@jit
def DistanceEstimator(positions, iterations, degree=8, bailout=1000):
    m = positions.shape[0]
    x, y, z = np.zeros(m), np.zeros(m), np.zeros(m)
    x0, y0, z0 = positions[:, 0], positions[:, 1], positions[:, 2]
    dr = np.zeros(m) + 1
    r = np.zeros(m)
    theta = np.zeros(m)
    phi = np.zeros(m)
    zr = np.zeros(m)
    for _ in range(iterations):
        r = np.sqrt(x*x + y*y + z*z)
        idx1 = r < bailout
        dr[idx1] = np.power(r[idx1], degree - 1) * degree * dr[idx1] + 1.0

        theta[idx1] = np.arctan2(np.sqrt(x[idx1]*x[idx1] + y[idx1]*y[idx1]), z[idx1])
        phi[idx1] = np.arctan2(y[idx1], x[idx1])

        zr[idx1] = r[idx1] ** degree
        theta[idx1] = theta[idx1] * degree
        phi[idx1] = phi[idx1] * degree

        x[idx1] = zr[idx1] * np.sin(theta[idx1]) * np.cos(phi[idx1]) + x0[idx1]
        y[idx1] = zr[idx1] * np.sin(theta[idx1]) * np.sin(phi[idx1]) + y0[idx1]
        z[idx1] = zr[idx1] * np.cos(theta[idx1]) + z0[idx1]

    return 0.5 * np.log(r) * r / dr