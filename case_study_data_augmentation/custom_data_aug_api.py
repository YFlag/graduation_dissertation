import math
import numpy as np

from PIL import Image


def rotate(im, theta=None, *, rotation_matrix=None, center=False):
    """ 
    rotate an image.
    1. the origin (0, 0) point is assumed to be bottom-left pixel of `im` . 
    2. the base coordinates preassumption: Descartes Coords.
    3. direction: theta is asssumed to be counter-clockwise. """
    
    """ paramater validation. """
    assert theta is not None or rotation_matrix is not None
    
    if theta is not None:
        rad = theta * math.pi / 180
        # print(theta, rad)
        rotation_matrix = np.array([[ math.cos(rad), -math.sin(rad),  0.        ],
                                    [ math.sin(rad),  math.cos(rad),  0.        ],
                                    [ 0.        ,  0.        ,  1.        ]])
        # print(rotation_matrix)
    elif rotation_matrix is not None:
        """ just use `rotation_matrix` directly. """
        pass
    if center == True:
        rotation_matrix = transform_matrix_offset_center(rotation_matrix, im.width, im.height)
        print(rotation_matrix)
    im_arr = np.array(im)
    im_t_arr = np.zeros_like(im)

    for x in range(im.width):
        for y in range(im.height):
            # print(x, y, end=' -> ')
            cur_coords = np.array([x, y, 1]).reshape(3, 1)
            new_x, new_y, _ = np.matmul(rotation_matrix, cur_coords).flatten()
            # print(new_x, new_y)
            # input()
            new_x, new_y = int(round(new_x)), int(round(new_y))
            if validate_coords(new_x, new_y, im):
                try:
                    """ convert Descartes coords to numpy array index coords. """
                    im_t_arr[im.height-new_y-1][new_x] = im_arr[im.height-y-1][x]
                except IndexError as e:
                    import pdb; pdb.set_trace()
                    pass
    return Image.fromarray(im_t_arr)


def transform_matrix_offset_center(matrix, x, y):
    """ copied from scipy. """
    o_x = float(x) / 2 + 0.5
    o_y = float(y) / 2 + 0.5
    offset_matrix = np.array([[1, 0, o_x], [0, 1, o_y], [0, 0, 1]])
    reset_matrix = np.array([[1, 0, -o_x], [0, 1, -o_y], [0, 0, 1]])
    transform_matrix = np.dot(np.dot(offset_matrix, matrix), reset_matrix)
    return transform_matrix


""" [todo] naming? """
def validate_coords(x, y, im):
    """ a valid x or y is assumed to be in the interval [0, width+1) or [0, height+1). """
    if x < 0 or y < 0:
        return False
    if x >= im.width:
        return False
    if y >= im.height:
        return False
    return True
