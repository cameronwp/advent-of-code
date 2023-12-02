(uiop:define-package #:aoc-2022-day-4
    (:use #:cl
          #:alexandria
          #:iterate))

(in-package #:aoc-2022-day-4)

;; FYI this is a very inefficient solution. doing math with bounds would have been way easier. not
;; sure what was going through my head today. I think I was dead set on practicing `iter'?

(defun get-range (elf)
  "Go from a string of l-u to a list of ints from l to u"
  (destructuring-bind (lower upper)
      (uiop:split-string elf :separator "-")
    (iter (for section from (parse-integer lower) to (parse-integer upper))
      (collecting section))))

;; it would be faster to just do math on the bounds. no need to actually build the ranges
(defun fully-contained (pair)
  (destructuring-bind (elf-1 elf-2)
      (uiop:split-string pair :separator ",")
    (let* ((range-1 (get-range elf-1))
           (range-2 (get-range elf-2))
           ;; sort the intersection just in case
           (overlap (sort (intersection range-1 range-2) '<)))
      (or (equal overlap range-1)
          (equal overlap range-2)))))

(defun part1 (filepath)
  (let ((pairs (uiop:read-file-lines filepath)))
    (iter (for pair in pairs)
      (counting (fully-contained pair)))))

(print (part1 "day-4-data.txt"))

;; there's no need to create the entire ranges to check the intersection of two ranges, but this
;; implementation barely required any modification from part1
(defun partially-contained (pair)
  (destructuring-bind (elf-1 elf-2)
      (uiop:split-string pair :separator ",")
    (let* ((range-1 (get-range elf-1))
           (range-2 (get-range elf-2))
           (overlap (intersection range-1 range-2)))
      (> (length overlap) 0))))

(defun part2 (filepath)
  (let ((pairs (uiop:read-file-lines filepath)))
    (iter (for pair in pairs)
      (counting (partially-contained pair)))))

(print (part2 "day-4-data.txt"))
