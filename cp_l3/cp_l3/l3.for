* Laboratory work
* Variant 13.2
*
* This file contain implementation of
* 1) matrix storage in sparse columnar format
* 2) multiplication of a matrix by a vector

* Plan:
* - allocate memory for sparse matrix
* - create read-function
* - create matrix_storage-structue & matrix_store-function
* - create vector_storage structure & vector_store-function
* - create matrix on vector multiplication function

* Issues:
* - How to allocate memory for as large array as possible?


      DIMENSION r_heap(*)
      open(1, file = 'dimensions.txt')
      read(1, *)i_a, i_b
      print *, i_a, i_b


1     format(A11)
      END



