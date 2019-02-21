# Mistake

## FFT

1. emm...                                                   (0)
1. When Diciding and making sub-Polynomial, "i ++" instead of
  "i += 2".                                                 (1)
1. When creating N-degree polynomial, push N numbers instead
  of pushing (N + 1) numbers includeing 0-term coefficient. (1)
1. Only get n point-value in DFT but answer need n + m.     (1)
1. Print extra suffix zero while printing answer.           (2)
1. Forget to Convert answer to integer while printing       (2)
1. Forget to divide each coefficient by N after DFT.        (2)
1. Make mistakes when calulating r array which is used for
  Rader sorting.                                            (1)
1. In Butterfly Operation, multiply $ W_n $ instead of
  $ W_n^k $.                                                (1)
1. Calculate R array error in Rader sort.                   (1)
1. Forget to run `W *= Wn` in every range in FFT            (2)

## LinkCutTree

1. emm...                                                   (0)
1. While rotating, set grandprant's son when grandprant's son
  is not THIS's father incorrectly.                         (1)
1. While cuting edge of x-y (x is y's father), only set x's
  son to NULL but forget to set y's father to NULL.         (1)
1. While cuting edge of x-y, only judge their connectivity but
  not judge if there's a edger of x-y.                      (1)

## Splay

1. emm...                                                   (0)
1. While rotating, forget to consider the case where son is
  empty.                                                    (1)
1. While rotating, set grandprant's son to THIS's father
  instead of THIS itself.                                   (1)

## Other

1. emm...                                                   (0)
1. While converting 'double' to 'int', forget to add 0.5.   (2)
1. After converting 'double' to 'int', the variable is still
  'double' and while printing it as answer, the 1000002 will
  be printed as 1e+6 and so on.                             (1)
1. While adding 0.5 to convert 'double' to 'int', forget it
  should be minus 0.5 when the number is less than zero.    (2)
1. Forget to break after some cases in 'switch'             (1)
1. Forget to initialize variables before use it.            (1)
1. If printing double by std::cout and not std::setprecision,
  it'll use scientific natatoin like 6.2333e+7 which will be
  inputed as 62333000 in special judge.                     (1)

