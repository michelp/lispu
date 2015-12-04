; test comment

(assert (== 3 3))
(assert (!= 3 4))
(assert (== (3 (+ 3 3) (- 3 3)) (3 6 0)))
(assert (== -3 -3))
(assert (== (1 2) (1 2)))
(assert (== (1 . 2) (1 . 2)))
(assert (not (== (1 . 2) (1 . 3))))
(assert (!= (1 . 2) (1 . 3)))
(assert (!= (1 1) (1 2)))
(assert (> 10 7))
(assert (< 1 4))
(assert (> 10 -4))
(assert (< -1 40))
(assert (== foo foo))
(assert (!= foo bar))
(assert (> foo bar))
(assert (< bar foo))

; comments?

(assert (is print (quote print))) ; comment ish
(assert (is (type print) fn1))
(assert (is (type 3) int))
(assert (is (type foo) symbol))
(assert (not (is (1 2) (1 2))))
(assert (isinstance 3 int))
(assert (isinstance 3 symbol))
(assert (isinstance foo symbol))
(assert (== (3 . (4 . (5 . nil))) (3 4 5)))
(assert (== (1 2 3) (1 2 3)))
(assert (not (== (1 2 3) (1 3 5))))
(assert (not (!= (1 2) (1 2))))
(assert (!= (1 2) (3 4)))
(assert (!= (1 2) (1 2 3)))
(assert (== (apply cons (3 4)) (3 . 4)))
(assert (== (eval (cons 3 4)) (3 . 4)))

(assert (is (if ()) nil))
(assert (== (if (true 1 2)) 1))
(assert (== (if (nil 1 2)) 2))

(assert (== (if ((== 3 4) (cons 1 2))) nil))
(assert (== (if ((== 4 4) (cons 1 2))) (1 . 2)))
(assert (== (if ((== 4 4) (cons 1 2) (cons 3 4))) (1 . 2)))
(assert (== (if ((== 4 5) (cons 1 2) (cons 3 4))) (3 . 4)))
(assert (== (if ((!= 4 4) (cons 1 2) (cons 3 4))) (3 . 4)))
(assert (all (== [1 2 3] [1 2 3])))
(assert (!= [1 2 3] [4 5 6]))

(assert (all (== (+ [1 2 3] [4 5 6]) [5 7 9])))
(assert (all (== (+ (fill 1 3) (fill 1 3)) [2 2 2])))

(assert (all [1 1 1]))
(assert (not (all [0 0 0])))
(assert (not (all [1 1 0])))

(assert (any [1 0 0]))
(assert (any [1 1 1]))
(assert (not (any [0 0 0])))

(println passed)
