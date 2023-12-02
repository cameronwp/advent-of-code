(uiop:define-package #:aoc2021/day3
  (:use #:cl
        #:bit-smasher))

(in-package #:aoc2021/day3)

(defun read-puzzle-input-lines (filename)
  (uiop:with-safe-io-syntax ()
    (uiop:read-file-lines (asdf:system-relative-pathname "aoc2021" (format nil "puzzle-inputs/~a" filename)))))

(defun read-puzzle-input-forms (filename)
  (uiop:with-safe-io-syntax ()
    (uiop:read-file-forms (asdf:system-relative-pathname "aoc2021" (format nil "puzzle-inputs/~a" filename)))))

;; operations on bit vectors
;; https://dept-info.labri.fr/~strandh/Teaching/MTP/Common/David-Lamkins/chapter18.html

(defparameter *test-report* '(00100
                              11110
                              10110
                              10111
                              10101
                              01111
                              00111
                              11100
                              10000
                              11001
                              00010
                              01010))

;; part 1
(print
 (let* ((report (read-puzzle-input-lines "day3.txt"))
        (summary '(0 0 0 0 0 0 0 0 0 0 0 0)))
   (loop for input in report
         for digits = (map 'list #'digit-char-p (coerce input 'list))
         do (setf summary (mapcar #'+ summary digits)))
   (*
    ;; gamma rate
    (bits->int (map 'bit-vector
                    #'(lambda (b) (if (> b 500) 1 0))
                    summary))
    ;; epsilon rate
    (bits->int (map 'bit-vector
                    #'(lambda (b) (if (< b 500) 1 0))
                    summary)))))

;; part 2

(defun str->list (input)
  "Convert a string of numbers into a list of its corresponding digits"
  ;; TODO: there's probably a better way of doing this
  (map 'list #'digit-char-p (coerce input 'list)))

(defun most-common-value (sum num)
  "Most common value"
  (if (>= sum (/ num 2)) 1 0))

(defun least-common-value (sum num)
  "Least common value"
  (if (= (most-common-value sum num) 1) 0 1))

(defun filter-o2 (n o2-lines o2-mcv)
  "Perform O2 algo by filtering the list of inputs based on MCV. Returns new list and new MCV"
  (if (= (list-length o2-lines) 1) o2-lines
      (loop for iline in o2-lines
            if (= (nth n iline) o2-mcv)
              ;; get the next set of lines ready
              append (list iline) into filtered-o2-lines and
              ;; update the next position if we haven't reached the end of the list
              if (< (1+ n) (list-length iline))
                sum (nth (1+ n) iline) into o2-mcv-next
            finally (return (values filtered-o2-lines (most-common-value o2-mcv-next (list-length filtered-o2-lines)))))))

(defun filter-co2 (n co2-lines co2-lcv)
  "Perform CO2 algo by filtering the list of inputs based on LCV. Returns new list and new LCV"
  (if (= (list-length co2-lines) 1) co2-lines
      (loop for iline in co2-lines
            if (= (nth n iline) co2-lcv)
              ;; get the next set of lines ready
              append (list iline) into filtered-co2-lines and
              ;; update the next position if we haven't reached the end of the list
              if (< (1+ n) (list-length iline))
                sum (nth (1+ n) iline) into co2-lcv-next
            finally (return (values filtered-co2-lines (least-common-value co2-lcv-next (list-length filtered-co2-lines)))))))

(defun filter-down-ratings (lines)
  (multiple-value-bind (lines-init o2-mcv-first)
      (loop for input in lines
            for iline = (str->list input)
            sum (car iline) into mcvs
            append (list iline) into ilines
            finally (return (values ilines (most-common-value mcvs (list-length ilines)))))
    (let* ((o2-lines (copy-list lines-init))
           (co2-lines (copy-list lines-init))
           (o2-mcv o2-mcv-first)
           ;; opposite of O2 - least common value
           (co2-lcv (if (= o2-mcv 1) 0 1)))

      ;; loop over all the bits
      (loop for n upto 11
            do (progn
                 ;; filter for the O2 generation rating
                 (multiple-value-bind (new-o2-lines new-o2-mcv)
                    (filter-o2 n o2-lines o2-mcv)
                   (setf o2-lines (copy-list new-o2-lines))
                   (setf o2-mcv new-o2-mcv))

                 ;; filter for the CO2 scrubbing rating
                 (multiple-value-bind (new-co2-lines new-co2-lcv)
                    (filter-co2 n co2-lines co2-lcv)
                   (setf co2-lines (copy-list new-co2-lines))
                   (setf co2-lcv new-co2-lcv)))
            finally (return (values o2-lines co2-lines))))))

(defun day3part2 ()
  "Day 3 part 2"
 (let* ((report (read-puzzle-input-lines "day3.txt")))
   (multiple-value-bind (o2-lines co2-lines)
       (filter-down-ratings report)
     (*
      (bits->int (car o2-lines))
      (bits->int (car co2-lines))))))

(print (day3part2))

