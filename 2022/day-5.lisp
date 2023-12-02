(uiop:define-package #:aoc-2022-day-5
    (:use #:cl
          #:cl-ppcre
          #:alexandria
          #:iterate))

(in-package #:aoc-2022-day-5)


(defun part1 (filepath)
  (let* ((raw-input (uiop:read-file-lines filepath))
         (input-length (length raw-input))
         ;; use this to find crates in each line later
         (crate-scanner (cl-ppcre:create-scanner "[A-Z]"))
         (move-start-pos 1) ; +1 for not counting the blank line
         ;; key is stack position, value is a list of crates where the top crate is the car
         (state (make-hash-table :test #'equal)))

    ;; build the initial state and figure out where the moves start
    (iter (for line in raw-input)
      (until (equal line ""))
      (incf move-start-pos)

      ;; get a list of (start1 stop1 start2 stop2 ...) positions for the crate ids
      (let* ((crate-bounds (cl-ppcre:all-matches crate-scanner line))
             (num-bounds (length crate-bounds)))

        ;; iterate over the start positions in the line to build each stack
        (iter (for c from 0 to num-bounds by 2)
          (until (> (1+ c) (length crate-bounds)))

          (let* ((crate-pos (first (subseq crate-bounds c (1+ c))))
                 (crate-name (subseq line crate-pos (1+ crate-pos)))
                 ;; for 0 indexed N:
                 ;; line num = 1 + N * 4
                 ;; N = (line num - 1) / 4
                 ;; then add 1 to 1-index it
                 (stack-id (1+ (/ (- crate-pos 1) 4)))
                 (stack-state (gethash stack-id state)))

            ;; it's easier to act on the car of the list with `pop'
            (setf (gethash stack-id state) (append stack-state (list crate-name)))))))

    ;; loop over moves and apply them
    (iter (for m from move-start-pos to (- input-length 1))
      (let* ((raw-move (first (subseq raw-input m (1+ m))))
             ;; it's easier to split on spaces rather than regex for 1 or 2 digit numbers
             (move-parts (uiop:split-string raw-move :separator " "))

             ;; parameters of each move
             (num-crates-to-move (parse-integer (first (subseq move-parts 1 2))))
             (start-stack-id (parse-integer (first (subseq move-parts 3 4))))
             (goal-stack-id (parse-integer (first (subseq move-parts 5 6)))))

        ;; follow the spirit of the procedure. `pop' works really well
        (dotimes (_x num-crates-to-move)
          (let ((crate (pop (gethash start-stack-id state)))
                (goal-stack (gethash goal-stack-id state)))
            (setf (gethash goal-stack-id state) (append (list crate) goal-stack))))))

    ;; grab the top of each stack. use an array so we ensure they're ordered correctly
    (let ((result (make-array (hash-table-count state))))
      (iter (for (stack-id stack) in-hashtable state)
        (setf (elt result (- stack-id 1)) (first stack)))

      ;; make the result easier to copy/paste
      (iter (for c in-sequence result)
        (format t "~A" c)))))

(part1 "day-5-data.txt")

(defun part2 (filepath)
  (let* ((raw-input (uiop:read-file-lines filepath))
         (input-length (length raw-input))
         ;; use this to find crates in each line later
         (crate-scanner (cl-ppcre:create-scanner "[A-Z]"))
         (move-start-pos 1) ; +1 for not counting the blank line
         ;; key is stack position, value is a list of crates where the top crate is the car
         (state (make-hash-table :test #'equal)))

    ;; build the initial state and figure out where the moves start
    (iter (for line in raw-input)
      (until (equal line ""))
      (incf move-start-pos)

      ;; get a list of (start1 stop1 start2 stop2 ...) positions for the crate ids
      (let* ((crate-bounds (cl-ppcre:all-matches crate-scanner line))
             (num-bounds (length crate-bounds)))

        ;; iterate over the start positions in the line to build each stack
        (iter (for c from 0 to num-bounds by 2)
          (until (> (1+ c) (length crate-bounds)))

          (let* ((crate-pos (first (subseq crate-bounds c (1+ c))))
                 (crate-name (subseq line crate-pos (1+ crate-pos)))
                 ;; for 0 indexed N:
                 ;; line num = 1 + N * 4
                 ;; N = (line num - 1) / 4
                 ;; then add 1 to 1-index it
                 (stack-id (1+ (/ (- crate-pos 1) 4)))
                 (stack-state (gethash stack-id state)))

            ;; it's easier to act on the car of the list with `pop'
            (setf (gethash stack-id state) (append stack-state (list crate-name)))))))

    ;; loop over moves and apply them
    (iter (for m from move-start-pos to (- input-length 1))
      (let* ((raw-move (first (subseq raw-input m (1+ m))))
             ;; it's easier to split on spaces rather than regex for 1 or 2 digit numbers
             (move-parts (uiop:split-string raw-move :separator " "))

             ;; parameters of each move
             (num-crates-to-move (parse-integer (first (subseq move-parts 1 2))))
             (start-stack-id (parse-integer (first (subseq move-parts 3 4))))
             (goal-stack-id (parse-integer (first (subseq move-parts 5 6))))

             (start-stack (gethash start-stack-id state))
             (goal-stack (gethash goal-stack-id state))
             (crates-being-moved (subseq start-stack 0 num-crates-to-move)))

        ;; remove the moved crates from the start stack
        (setf (gethash start-stack-id state) (subseq start-stack num-crates-to-move))
        ;; prepend the moved crates to the goal stack
        (setf (gethash goal-stack-id state) (append crates-being-moved goal-stack))))

    ;; (print (alexandria:hash-table-values state))

    ;; grab the top of each stack. use an array so we ensure they're ordered correctly
    (let ((result (make-array (hash-table-count state))))
      (iter (for (stack-id stack) in-hashtable state)
        (setf (elt result (- stack-id 1)) (first stack)))

      ;; make the result easier to copy/paste
      (iter (for c in-sequence result)
        (format t "~A" c)))))

(part2 "day-5-data.txt")
