
(assert (all (== (+ (fill 1 7500000) (fill 1 7500000)) (+ (fill 1 7500000) (fill 1 7500000)))))
(assert (all (== (+ (fill 1 7500000) (fill 1 7500000)) (+ (fill 1 7500000) (fill 1 7500000)))))
(assert (all (== (+ (fill 1 7500000) (fill 1 7500000)) (+ (fill 1 7500000) (fill 1 7500000)))))
(assert (any (== (+ (fill 1 7500000) (fill 1 7500000)) (+ (fill 1 7500000) (fill 1 7500000)))))
(assert (any (== (+ (fill 1 7500000) (fill 1 7500000)) (+ (fill 1 7500000) (fill 1 7500000)))))
(assert (any (== (+ (fill 1 7500000) (fill 1 7500000)) (+ (fill 1 7500000) (fill 1 7500000)))))
(gc)

(assert
 (all
  (==
   (+ (fill 1 7500000)
      (+ (fill 1 7500000)
         (+ (fill 1 7500000)
            (+ (fill 1 7500000)
               (+ (fill 1 7500000)
                  (+ (fill 1 7500000)
                     (+ (fill 1 7500000)
                        (+ (fill 1 7500000)
                           (+ (fill 1 7500000)
                              (fill 1 7500000))))))))))
   (fill 10 7500000)
   )
  )
 )

(gc)

(assert (all (== (fma (fill 1 7500000) (fill 1 7500000) (fill 1 7500000)) (fma (fill 1 7500000) (fill 1 7500000) (fill 1 7500000)))))
(assert (all (== (fma (fill 1 7500000) (fill 1 7500000) (fill 1 7500000)) (fma (fill 1 7500000) (fill 1 7500000) (fill 1 7500000)))))
(assert (all (== (fma (fill 1 7500000) (fill 1 7500000) (fill 1 7500000)) (fma (fill 1 7500000) (fill 1 7500000) (fill 1 7500000)))))
(assert (any (== (fma (fill 1 7500000) (fill 1 7500000) (fill 1 7500000)) (fma (fill 1 7500000) (fill 1 7500000) (fill 1 7500000)))))
(assert (any (== (fma (fill 1 7500000) (fill 1 7500000) (fill 1 7500000)) (fma (fill 1 7500000) (fill 1 7500000) (fill 1 7500000)))))
(assert (any (== (fma (fill 1 7500000) (fill 1 7500000) (fill 1 7500000)) (fma (fill 1 7500000) (fill 1 7500000) (fill 1 7500000)))))

(gc)
(println passed)
