(defsystem #:aoc2021
  :name "Advent of Code 2021"
  :pathname "src"
  :components ((:file "day1")
               (:file "day2"))
  :depends-on ("bit-smasher"
               "cl-ppcre"))
