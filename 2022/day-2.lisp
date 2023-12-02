(uiop:define-package #:aoc-2022-day-2
    (:use #:cl
          #:alexandria
          #:iterate))

(in-package #:aoc-2022-day-2)

;; A for Rock, B for Paper, and C for Scissors
;; X for Rock, Y for Paper, and Z for Scissors
;;
;; The score for a single round is the score for the shape you selected (1 for Rock, 2 for Paper,
;; and 3 for Scissors) plus the score for the outcome of the round (0 if you lost, 3 if the round
;; was a draw, and 6 if you won)

(defun did-we-win (them us)
  (or (and (equal them "A") (equal us "Y"))
      (and (equal them "B") (equal us "Z"))
      (and (equal them "C") (equal us "X")))

(defun part1 (filepath)
  (let ((raw-input (uiop:read-file-lines filepath))
        (scoring (list (cons "A" 1)
                       (cons "B" 2)
                       (cons "C" 3)
                       (cons "X" 1)
                       (cons "Y" 2)
                       (cons "Z" 3))))
    (flet ((get-score (them us)
             ;; eg. A Y means they played rock and we played paper
             (let* ((our-score (alexandria:assoc-value scoring us :test #'equal))
                    (their-score (alexandria:assoc-value scoring them :test #'equal))
                    (won (did-we-win them us))
                    (draw (equal our-score their-score)))
               (+ our-score (if draw 3 (if won 6 0))))))
      (iter (for input in raw-input)
        (summing (get-score (subseq input 0 1) (subseq input 2 3)))))))

(print (part1 "day-2-data.txt"))

;; X means you need to lose, Y means you need to end the round in a draw, and Z means you need to
;; win.

(defun part2 (filepath)
  (let ((raw-input (uiop:read-file-lines filepath))
        (shapes (list 1 2 3))
        (scoring (list (cons "A" 1)
                       (cons "B" 2)
                       (cons "C" 3)
                       (cons "X" 0)
                       (cons "Y" 3)
                       (cons "Z" 6))))
    (flet ((enforce-result (them result)
             ;; eg. A Y means they played rock and we need to tie
             (let* ((our-score (alexandria:assoc-value scoring result :test #'equal))
                    (their-score (alexandria:assoc-value scoring them :test #'equal))
                    (their-index (- their-score 1))
                    (our-shape (cond ((equal result "X") (nth-pos-neg (- their-index 1) shapes)) ; lose
                                     ((equal result "Y") their-score) ; draw
                                     ((equal result "Z") (nth-pos-neg (1+ their-index) shapes)) ; win
                                     (t 0))))
               (+ our-score our-shape))))
      (iter (for input in raw-input)
        (summing (enforce-result (subseq input 0 1) (subseq input 2 3)))))))

(print (part2 "day-2-data.txt"))

;;; From https://github.com/martinkersner/cl-math/blob/master/list.lisp#L29
;; Creates valid index in list.
(defun circular-index (idx lst)
  (let* ((l (length lst))
         (new-idx (mod (abs idx) l))
         (start-idx (if (< idx 0)
                      (if (equal new-idx 0)
                        (progn
                          (setf new-idx 0)
                          0)
                        (progn
                          (setf new-idx (- new-idx))
                          l))
                      0)))

    (+ start-idx new-idx)))

;; Access list with positive or negative index.
(defun nth-pos-neg (idx lst)
  (nth (circular-index idx lst) lst))
