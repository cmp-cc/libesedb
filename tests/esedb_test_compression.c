/*
 * Library compression functions test program
 *
 * Copyright (C) 2009-2018, Joachim Metz <joachim.metz@gmail.com>
 *
 * Refer to AUTHORS for acknowledgements.
 *
 * This software is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This software is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this software.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <common.h>
#include <file_stream.h>
#include <memory.h>
#include <types.h>

#if defined( HAVE_STDLIB_H ) || defined( WINAPI )
#include <stdlib.h>
#endif

#include "esedb_test_libcerror.h"
#include "esedb_test_libesedb.h"
#include "esedb_test_macros.h"
#include "esedb_test_memory.h"
#include "esedb_test_unused.h"

#include "../libesedb/libesedb_compression.h"

uint8_t esedb_test_compression_7bit_compressed_data[ 50 ] = {
	0x10, 0xd2, 0xa2, 0x0e, 0x04, 0x42, 0xbd, 0x82, 0xf2, 0x31, 0x3a, 0x5d, 0x36, 0xb7, 0xc3, 0x70,
	0x78, 0xd9, 0xfd, 0xb2, 0x96, 0xe5, 0xf7, 0xb4, 0x9a, 0x5c, 0x96, 0x93, 0xcb, 0xa0, 0x34, 0xbd,
	0xdc, 0x9e, 0xbf, 0xac, 0x65, 0xb9, 0xfe, 0xed, 0x26, 0x97, 0xdd, 0xa0, 0x34, 0xbd, 0xdc, 0x9e,
	0xa7, 0x00
};

uint8_t esedb_test_compression_7bit_uncompressed_data[ 56 ] = {
	0x52, 0x45, 0x3a, 0x20, 0x20, 0x28, 0x2f, 0x41, 0x72, 0x63, 0x68, 0x69, 0x65, 0x66, 0x6d, 0x61, 
	0x70, 0x70, 0x65, 0x6e, 0x2f, 0x56, 0x65, 0x72, 0x77, 0x69, 0x6a, 0x64, 0x65, 0x72, 0x64, 0x65, 
	0x20, 0x69, 0x74, 0x65, 0x6d, 0x73, 0x2f, 0x56, 0x65, 0x72, 0x7a, 0x6f, 0x6e, 0x64, 0x65, 0x6e, 
	0x20, 0x69, 0x74, 0x65, 0x6d, 0x73, 0x29, 0x00
};

#if defined( __GNUC__ ) && !defined( LIBESEDB_DLL_IMPORT )

/* Tests the libesedb_compression_7bit_decompress_get_size function
 * Returns 1 if successful or 0 if not
 */
int esedb_test_compression_7bit_decompress_get_size(
     void )
{
	libcerror_error_t *error      = NULL;
	size_t uncompressed_data_size = 0;
	int result                    = 0;

	/* Test regular cases
	 */
	result = libesedb_compression_7bit_decompress_get_size(
	          esedb_test_compression_7bit_compressed_data,
	          50,
	          &uncompressed_data_size,
	          &error );

	ESEDB_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	ESEDB_TEST_ASSERT_EQUAL_SIZE(
	 "uncompressed_data_size",
	 uncompressed_data_size,
	 (size_t) 56 );

	ESEDB_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test error cases
	 */
	result = libesedb_compression_7bit_decompress_get_size(
	          NULL,
	          50,
	          &uncompressed_data_size,
	          &error );

	ESEDB_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	ESEDB_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	result = libesedb_compression_7bit_decompress_get_size(
	          esedb_test_compression_7bit_compressed_data,
	          (size_t) SSIZE_MAX + 1,
	          &uncompressed_data_size,
	          &error );

	ESEDB_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	ESEDB_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	result = libesedb_compression_7bit_decompress_get_size(
	          esedb_test_compression_7bit_compressed_data,
	          50,
	          NULL,
	          &error );

	ESEDB_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	ESEDB_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	return( 0 );
}

/* Tests the libesedb_compression_7bit_decompress function
 * Returns 1 if successful or 0 if not
 */
int esedb_test_compression_7bit_decompress(
     void )
{
	uint8_t uncompressed_data[ 64 ];

	libcerror_error_t *error = NULL;
	int result               = 0;

	/* Test regular cases
	 */
	result = libesedb_compression_7bit_decompress(
	          esedb_test_compression_7bit_compressed_data,
	          50,
	          uncompressed_data,
	          64,
	          &error );

	ESEDB_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	ESEDB_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = memory_compare(
	          uncompressed_data,
	          esedb_test_compression_7bit_uncompressed_data,
	          56 );

	ESEDB_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 0 );

	/* Test error cases
	 */
	result = libesedb_compression_7bit_decompress(
	          NULL,
	          50,
	          uncompressed_data,
	          64,
	          &error );

	ESEDB_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	ESEDB_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	result = libesedb_compression_7bit_decompress(
	          esedb_test_compression_7bit_compressed_data,
	          (size_t) SSIZE_MAX + 1,
	          uncompressed_data,
	          64,
	          &error );

	ESEDB_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	ESEDB_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	result = libesedb_compression_7bit_decompress(
	          esedb_test_compression_7bit_compressed_data,
	          50,
	          NULL,
	          64,
	          &error );

	ESEDB_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	ESEDB_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	result = libesedb_compression_7bit_decompress(
	          esedb_test_compression_7bit_compressed_data,
	          50,
	          uncompressed_data,
	          (size_t) SSIZE_MAX + 1,
	          &error );

	ESEDB_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	ESEDB_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	return( 0 );
}

#endif /* defined( __GNUC__ ) && !defined( LIBESEDB_DLL_IMPORT ) */

/* The main program
 */
#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
int wmain(
     int argc ESEDB_TEST_ATTRIBUTE_UNUSED,
     wchar_t * const argv[] ESEDB_TEST_ATTRIBUTE_UNUSED )
#else
int main(
     int argc ESEDB_TEST_ATTRIBUTE_UNUSED,
     char * const argv[] ESEDB_TEST_ATTRIBUTE_UNUSED )
#endif
{
	ESEDB_TEST_UNREFERENCED_PARAMETER( argc )
	ESEDB_TEST_UNREFERENCED_PARAMETER( argv )

#if defined( __GNUC__ ) && !defined( LIBESEDB_DLL_IMPORT )

	ESEDB_TEST_RUN(
	 "libesedb_compression_7bit_decompress_get_size",
	 esedb_test_compression_7bit_decompress_get_size );

	ESEDB_TEST_RUN(
	 "libesedb_compression_7bit_decompress",
	 esedb_test_compression_7bit_decompress );

	/* TODO: add tests for libesedb_compression_xpress_decompress_get_size */

	/* TODO: add tests for libesedb_compression_xpress_decompress */

	/* TODO: add tests for libesedb_compression_decompress_get_size */

	/* TODO: add tests for libesedb_compression_decompress */

	/* TODO: add tests for libesedb_compression_get_utf8_string_size */

	/* TODO: add tests for libesedb_compression_copy_to_utf8_string */

	/* TODO: add tests for libesedb_compression_get_utf16_string_size */

	/* TODO: add tests for libesedb_compression_copy_to_utf16_string */

#endif /* defined( __GNUC__ ) && !defined( LIBESEDB_DLL_IMPORT ) */

	return( EXIT_SUCCESS );

on_error:
	return( EXIT_FAILURE );
}
