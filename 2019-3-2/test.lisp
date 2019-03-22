(setf n (read)
      m (read))
(setf a (make-array 15 :initial-element 0)
      x (make-array 15 :initial-element 0)
      delta (make-array 15 :initial-element 0)
      lch (make-array 15 :initial-element 0)
      rch (make-array 15 :initial-element 0))
(setf sz 1)
(defun upd(cur)
    (setf (svref x cur) (+ (svref x (svref lch cur)) (svref x (svref rch cur)))))
(defun build(l r)
    (setf cur (+ sz 1))
    (setf sz (+ sz 1))
    (if (= l r)
        (setf (svref x cur) (svref a l))
        (progn
            (setf mid (truncate (/ (+ l r) 2)))
            (setf (svref lch cur) (build l mid))
            (setf mid (truncate (/ (+ l r) 2)))
            (setf (svref rch cur) (build (+ mid 1) r))
            (upd cur)))
    cur)
(do ((i 1 (+ i 1)))
    ((> i n) 'done)
    (setf (svref a i) (read)))
(build 1 n)
(format t "~A~%" x)
(format t "~A~%" lch)
(format t "~A~%" rch)
