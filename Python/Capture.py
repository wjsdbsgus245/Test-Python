# -*- coding: utf-8 -*- 

import time

import mss
import cv2
import numpy

with mss.mss() as sct:
    monitor = {"top" : 0, "left" : 0, "width" : 1280, "height" : 800}

    while "Screen Capturing":
        last_time = time.time()
    
        img = numpy.array(sct.grab(monitor))

        cv2.imshow("OpenCV/Numpy normal", img)
        #fps = 1 / (time.time() - last_time)
        print("fps : {0}".format(1 / (time.time() - last_time)))

        if cv2.waitKey(25) & 0xFF == ord('q'):
            cv2.destroyAllWindows()
            break
