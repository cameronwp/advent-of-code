(uiop:define-package #:aoc-2022-day-1
    (:use #:cl
          #:iterate))

(in-package #:aoc-2022-day-1)

(defun part1 (filepath)
  (let ((raw-input (uiop:read-file-lines filepath))
        (elf-with-most-cals 0)
        (most-so-far 0)
        (curr-cals 0))
    (iter (for line in raw-input)
      (let ((val (or (parse-integer line :junk-allowed t) 0)))
        (incf curr-cals val)

        (when (equal line "")
          (when (> curr-cals most-so-far)
            (setf most-so-far curr-cals))
          (setf curr-cals 0))))
    most-so-far))

(print (part1 "day-1-data.txt"))

(defun part2 (filepath)
  (let ((raw-input (uiop:read-file-lines filepath))
        (top-3 (list 0 0 0))
        (curr-cals 0))
    (iter (for line in raw-input)
      (let ((val (or (parse-integer line :junk-allowed t) 0)))
        (incf curr-cals val)

        (when (equal line "")
          (let ((best-3 (subseq (sort (cons curr-cals top-3) #'>) 0 3)))
            (setf top-3 best-3))
          (setf curr-cals 0))))
    (apply '+ top-3)))

(print (part2 "day-1-data.txt"))
