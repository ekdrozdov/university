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


      DIMENSION r_heap(100000)
      DIMENSION vector(100)
      DIMENSION ia(100), di(100), ja(100), al(100), au(100)


      i_desc = 1
* Read dimensions
      open(i_desc, file = 'dimensions.txt')
      read(i_desc, *) i_matrix_high, i_matrix_lenght, i_vector_dim
      close(i_desc)
!      print *, 'Matrix dim:', i_matrix_high, i_matrix_lenght
!      print *, 'Vector dim:', i_vector_dim

* Read vector
      read_vector(vector)

* Read matrix


* Multiply matrix by vector



      pause: 'Press enter to exit...'

1     format(A11)
      END



