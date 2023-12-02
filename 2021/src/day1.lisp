;;;; -*- Mode: common-lisp; -*-

;; https://adventofcode.com/2021/day/1

;; part 1
(print
 (loop
   for depth in (uiop:read-file-lines "day1-data.txt")
   if (and
       (not (null history))
       (> (parse-integer depth) (car (last history))))
     count depth into total
   append (list (parse-integer depth)) into history
   finally
      (return total)))

;; part 2
(defparameter *test-nums* '(
                            "199"
                            "200"
                            "208"
                            "210"
                            "200"
                            "207"
                            "240"
                            "269"
                            "260"
                            "263"
                            ))

(defun sum (nums)
  "Get the sum of a list of numbers"
  (reduce #'+ nums))

(print
 (loop
   for depth in (uiop:read-file-lines "day1-data.txt")
   ;; for depth in *test-nums*
   if (and
       (not (null history))
       (>= (list-length history) 3)
       (> (sum (append (list (parse-integer depth)) (last history 2)))
          (sum (last history 3))))
     count depth into total
   append (list (parse-integer depth)) into history
   finally
      (return total)))
