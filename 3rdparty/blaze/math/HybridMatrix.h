//=================================================================================================
/*!
//  \file blaze/math/HybridMatrix.h
//  \brief Header file for the complete HybridMatrix implementation
//
//  Copyright (C) 2012-2020 Klaus Iglberger - All Rights Reserved
//
//  This file is part of the Blaze library. You can redistribute it and/or modify it under
//  the terms of the New (Revised) BSD License. Redistribution and use in source and binary
//  forms, with or without modification, are permitted provided that the following conditions
//  are met:
//
//  1. Redistributions of source code must retain the above copyright notice, this list of
//     conditions and the following disclaimer.
//  2. Redistributions in binary form must reproduce the above copyright notice, this list
//     of conditions and the following disclaimer in the documentation and/or other materials
//     provided with the distribution.
//  3. Neither the names of the Blaze development group nor the names of its contributors
//     may be used to endorse or promote products derived from this software without specific
//     prior written permission.
//
//  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY
//  EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
//  OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT
//  SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
//  INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED
//  TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR
//  BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
//  CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
//  ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH
//  DAMAGE.
*/
//=================================================================================================

#ifndef _BLAZE_MATH_HYBRIDMATRIX_H_
#define _BLAZE_MATH_HYBRIDMATRIX_H_


//*************************************************************************************************
// Includes
//*************************************************************************************************

#include "../math/dense/HybridMatrix.h"
#include "../math/DenseMatrix.h"
#include "../math/Exception.h"
#include "../math/HybridVector.h"
#include "../math/IdentityMatrix.h"
#include "../math/shims/Conjugate.h"
#include "../math/shims/Real.h"
#include "../math/StaticMatrix.h"
#include "../math/typetraits/UnderlyingBuiltin.h"
#include "../math/ZeroMatrix.h"
#include "../util/Assert.h"
#include "../util/constraints/Numeric.h"
#include "../util/Random.h"


namespace blaze {

//=================================================================================================
//
//  RAND SPECIALIZATION
//
//=================================================================================================

//*************************************************************************************************
/*! \cond BLAZE_INTERNAL */
/*!\brief Specialization of the Rand class template for HybridMatrix.
// \ingroup random
//
// This specialization of the Rand class creates random instances of HybridMatrix.
*/
template< typename Type  // Data type of the matrix
        , size_t M       // Number of rows
        , size_t N       // Number of columns
        , bool SO >      // Storage order
class Rand< HybridMatrix<Type,M,N,SO> >
{
 public:
   //**Generate functions**************************************************************************
   /*!\name Generate functions */
   //@{
   inline const HybridMatrix<Type,M,N,SO> generate( size_t m, size_t n ) const;

   template< typename Arg >
   inline const HybridMatrix<Type,M,N,SO> generate( size_t m, size_t n, const Arg& min, const Arg& max ) const;
   //@}
   //**********************************************************************************************

   //**Randomize functions*************************************************************************
   /*!\name Randomize functions */
   //@{
   inline void randomize( HybridMatrix<Type,M,N,SO>& matrix ) const;

   template< typename Arg >
   inline void randomize( HybridMatrix<Type,M,N,SO>& matrix, const Arg& min, const Arg& max ) const;
   //@}
   //**********************************************************************************************
};
/*! \endcond */
//*************************************************************************************************


//*************************************************************************************************
/*! \cond BLAZE_INTERNAL */
/*!\brief Generation of a random HybridMatrix.
//
// \return The generated random matrix.
*/
template< typename Type  // Data type of the matrix
        , size_t M       // Number of rows
        , size_t N       // Number of columns
        , bool SO >      // Storage order
inline const HybridMatrix<Type,M,N,SO>
   Rand< HybridMatrix<Type,M,N,SO> >::generate( size_t m, size_t n ) const
{
   HybridMatrix<Type,M,N,SO> matrix( m, n );
   randomize( matrix );
   return matrix;
}
/*! \endcond */
//*************************************************************************************************


//*************************************************************************************************
/*! \cond BLAZE_INTERNAL */
/*!\brief Generation of a random HybridMatrix.
//
// \param min The smallest possible value for a matrix element.
// \param max The largest possible value for a matrix element.
// \return The generated random matrix.
*/
template< typename Type   // Data type of the matrix
        , size_t M        // Number of rows
        , size_t N        // Number of columns
        , bool SO >       // Storage order
template< typename Arg >  // Min/max argument type
inline const HybridMatrix<Type,M,N,SO>
   Rand< HybridMatrix<Type,M,N,SO> >::generate( size_t m, size_t n, const Arg& min, const Arg& max ) const
{
   HybridMatrix<Type,M,N,SO> matrix( m, n );
   randomize( matrix, min, max );
   return matrix;
}
/*! \endcond */
//*************************************************************************************************


//*************************************************************************************************
/*! \cond BLAZE_INTERNAL */
/*!\brief Randomization of a HybridMatrix.
//
// \param matrix The matrix to be randomized.
// \return void
*/
template< typename Type  // Data type of the matrix
        , size_t M       // Number of rows
        , size_t N       // Number of columns
        , bool SO >      // Storage order
inline void Rand< HybridMatrix<Type,M,N,SO> >::randomize( HybridMatrix<Type,M,N,SO>& matrix ) const
{
   using blaze::randomize;

   const size_t m( matrix.rows()    );
   const size_t n( matrix.columns() );

   for( size_t i=0UL; i<m; ++i ) {
      for( size_t j=0UL; j<n; ++j ) {
         randomize( matrix(i,j) );
      }
   }
}
/*! \endcond */
//*************************************************************************************************


//*************************************************************************************************
/*! \cond BLAZE_INTERNAL */
/*!\brief Randomization of a HybridMatrix.
//
// \param matrix The matrix to be randomized.
// \param min The smallest possible value for a matrix element.
// \param max The largest possible value for a matrix element.
// \return void
*/
template< typename Type   // Data type of the matrix
        , size_t M        // Number of rows
        , size_t N        // Number of columns
        , bool SO >       // Storage order
template< typename Arg >  // Min/max argument type
inline void Rand< HybridMatrix<Type,M,N,SO> >::randomize( HybridMatrix<Type,M,N,SO>& matrix,
                                                          const Arg& min, const Arg& max ) const
{
   using blaze::randomize;

   const size_t m( matrix.rows()    );
   const size_t n( matrix.columns() );

   for( size_t i=0UL; i<m; ++i ) {
      for( size_t j=0UL; j<n; ++j ) {
         randomize( matrix(i,j), min, max );
      }
   }
}
/*! \endcond */
//*************************************************************************************************




//=================================================================================================
//
//  MAKE FUNCTIONS
//
//=================================================================================================

//*************************************************************************************************
/*! \cond BLAZE_INTERNAL */
/*!\brief Setup of a random symmetric HybridMatrix.
//
// \param matrix The matrix to be randomized.
// \return void
// \exception std::invalid_argument Invalid non-square matrix provided.
*/
template< typename Type  // Data type of the matrix
        , size_t M       // Number of rows
        , size_t N       // Number of columns
        , bool SO >      // Storage order
void makeSymmetric( HybridMatrix<Type,M,N,SO>& matrix )
{
   using blaze::randomize;

   if( !isSquare( ~matrix ) ) {
      BLAZE_THROW_INVALID_ARGUMENT( "Invalid non-square matrix provided" );
   }

   const size_t n( matrix.rows() );

   for( size_t i=0UL; i<n; ++i ) {
      for( size_t j=0UL; j<i; ++j ) {
         randomize( matrix(i,j) );
         matrix(j,i) = matrix(i,j);
      }
      randomize( matrix(i,i) );
   }

   BLAZE_INTERNAL_ASSERT( isSymmetric( matrix ), "Non-symmetric matrix detected" );
}
/*! \endcond */
//*************************************************************************************************


//*************************************************************************************************
/*! \cond BLAZE_INTERNAL */
/*!\brief Setup of a random symmetric HybridMatrix.
//
// \param matrix The matrix to be randomized.
// \param min The smallest possible value for a matrix element.
// \param max The largest possible value for a matrix element.
// \return void
// \exception std::invalid_argument Invalid non-square matrix provided.
*/
template< typename Type   // Data type of the matrix
        , size_t M        // Number of rows
        , size_t N        // Number of columns
        , bool SO         // Storage order
        , typename Arg >  // Min/max argument type
void makeSymmetric( HybridMatrix<Type,M,N,SO>& matrix, const Arg& min, const Arg& max )
{
   using blaze::randomize;

   if( !isSquare( ~matrix ) ) {
      BLAZE_THROW_INVALID_ARGUMENT( "Invalid non-square matrix provided" );
   }

   const size_t n( matrix.rows() );

   for( size_t i=0UL; i<n; ++i ) {
      for( size_t j=0UL; j<i; ++j ) {
         randomize( matrix(i,j), min, max );
         matrix(j,i) = matrix(i,j);
      }
      randomize( matrix(i,i), min, max );
   }

   BLAZE_INTERNAL_ASSERT( isSymmetric( matrix ), "Non-symmetric matrix detected" );
}
/*! \endcond */
//*************************************************************************************************


//*************************************************************************************************
/*! \cond BLAZE_INTERNAL */
/*!\brief Setup of a random Hermitian HybridMatrix.
//
// \param matrix The matrix to be randomized.
// \return void
// \exception std::invalid_argument Invalid non-square matrix provided.
*/
template< typename Type  // Data type of the matrix
        , size_t M       // Number of rows
        , size_t N       // Number of columns
        , bool SO >      // Storage order
void makeHermitian( HybridMatrix<Type,M,N,SO>& matrix )
{
   using blaze::randomize;

   BLAZE_CONSTRAINT_MUST_BE_NUMERIC_TYPE( Type );

   using BT = UnderlyingBuiltin_t<Type>;

   if( !isSquare( ~matrix ) ) {
      BLAZE_THROW_INVALID_ARGUMENT( "Invalid non-square matrix provided" );
   }

   const size_t n( matrix.rows() );

   for( size_t i=0UL; i<n; ++i ) {
      for( size_t j=0UL; j<i; ++j ) {
         randomize( matrix(i,j) );
         matrix(j,i) = conj( matrix(i,j) );
      }
      matrix(i,i) = rand<BT>();
   }

   BLAZE_INTERNAL_ASSERT( isHermitian( matrix ), "Non-Hermitian matrix detected" );
}
/*! \endcond */
//*************************************************************************************************


//*************************************************************************************************
/*! \cond BLAZE_INTERNAL */
/*!\brief Setup of a random Hermitian HybridMatrix.
//
// \param matrix The matrix to be randomized.
// \param min The smallest possible value for a matrix element.
// \param max The largest possible value for a matrix element.
// \return void
// \exception std::invalid_argument Invalid non-square matrix provided.
*/
template< typename Type   // Data type of the matrix
        , size_t M        // Number of rows
        , size_t N        // Number of columns
        , bool SO         // Storage order
        , typename Arg >  // Min/max argument type
void makeHermitian( HybridMatrix<Type,M,N,SO>& matrix, const Arg& min, const Arg& max )
{
   using blaze::randomize;

   BLAZE_CONSTRAINT_MUST_BE_NUMERIC_TYPE( Type );

   using BT = UnderlyingBuiltin_t<Type>;

   if( !isSquare( ~matrix ) ) {
      BLAZE_THROW_INVALID_ARGUMENT( "Invalid non-square matrix provided" );
   }

   const size_t n( matrix.rows() );

   for( size_t i=0UL; i<n; ++i ) {
      for( size_t j=0UL; j<i; ++j ) {
         randomize( matrix(i,j), min, max );
         matrix(j,i) = conj( matrix(i,j) );
      }
      matrix(i,i) = rand<BT>( real( min ), real( max ) );
   }

   BLAZE_INTERNAL_ASSERT( isHermitian( matrix ), "Non-Hermitian matrix detected" );
}
/*! \endcond */
//*************************************************************************************************


//*************************************************************************************************
/*! \cond BLAZE_INTERNAL */
/*!\brief Setup of a random (Hermitian) positive definite HybridMatrix.
//
// \param matrix The matrix to be randomized.
// \return void
// \exception std::invalid_argument Invalid non-square matrix provided.
*/
template< typename Type  // Data type of the matrix
        , size_t M       // Number of rows
        , size_t N       // Number of columns
        , bool SO >      // Storage order
void makePositiveDefinite( HybridMatrix<Type,M,N,SO>& matrix )
{
   using blaze::randomize;

   BLAZE_CONSTRAINT_MUST_BE_NUMERIC_TYPE( Type );

   if( !isSquare( ~matrix ) ) {
      BLAZE_THROW_INVALID_ARGUMENT( "Invalid non-square matrix provided" );
   }

   const size_t n( matrix.rows() );

   randomize( matrix );
   matrix *= ctrans( matrix );

   for( size_t i=0UL; i<n; ++i ) {
      matrix(i,i) += Type(n);
   }

   BLAZE_INTERNAL_ASSERT( isHermitian( matrix ), "Non-symmetric matrix detected" );
}
/*! \endcond */
//*************************************************************************************************

} // namespace blaze

#endif
