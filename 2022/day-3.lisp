(uiop:define-package #:aoc-2022-day-3
    (:use #:cl
          #:alexandria
          #:iterate))

(in-package #:aoc-2022-day-3)

(defun value-of (char)
  (let ((ascii (char-code char)))
    (if (>= ascii 97)
        ;; must be lower case. start at a=1
        (- ascii 96)
        ;; must be upper case. start at A=27
        (- ascii 38))))

(defun string-to-char-list (str)
  (coerce str 'list))

(defun part1 (filepath)
  (let ((raw-input (uiop:read-file-lines filepath)))
    (flet ((get-value (rucksack)
             (let* ((num-items (length rucksack))
                    (compartment-1 (subseq rucksack 0 (/ num-items 2)))
                    (compartment-2 (subseq rucksack (/ num-items 2) num-items))
                    (shared (remove-duplicates (intersection
                                                (string-to-char-list compartment-1)
                                                (string-to-char-list compartment-2))))
                    (shared-values (map 'list #'value-of shared)))
               ;; map it just in case multiple items are shared
               (apply '+ shared-values))))
      (iter (for rucksack in raw-input)
        (summing (get-value rucksack))))))

(print (part1 "day-3-data.txt"))

(defun part2 (filepath)
  (let* ((raw-input (uiop:read-file-lines filepath))
         (num-lines (length raw-input)))
    (flet ((get-value (rucksacks)
             (let* ((rucksacks-as-char-lists (map 'list 'string-to-char-list rucksacks))
                    (shared (remove-duplicates (reduce 'intersection rucksacks-as-char-lists)))
                    (shared-values (map 'list #'value-of shared)))
               (apply '+ shared-values))))
      (iter (for r from 0 to num-lines by 3)
        (until (equal r 300))
        (summing (get-value (subseq raw-input r (+ r 3))))))))

(print (part2 "day-3-data.txt"))
