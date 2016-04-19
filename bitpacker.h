#pragma once
#include <stdint.h>
#include <stddef.h>

/*!
 * @brief BitPacker object. 
 *
 * Holds the pointer to the buffer to write the data to and the actual position inside the buffer.
 */
typedef struct
{
    /*!
     * @brief Position in bits of input/output cursor on the buffer.
     */
    size_t bitPosition;
    
    /*!
     * @brief The size of the buffer in bits.
     */
    size_t bitSize;
    
    /*!
     * @brief The pointer to the start of the buffer used to write the bits into.
     */
    uint8_t * data;
} BitPacker;

/*!
 * @brief Initializes the bit packer pointed by packer. This method has to be called before any other.
 *
 * @param packer    Pointer to the packer to initialize.
 * @param buffer    Pointer to the memory region into which the packer has to write the bits.
 * @param byteSize  The size of the buffer in bytes.
 * @return          0 on success, -1 on error.
 */
int bitPackerInit( BitPacker * packer , uint8_t * buffer , size_t byteSize );

/*!
 * @brief Returns the number of free bits left on the buffer either to read or to write.
 *
 * @param packer    Pointer to the packer to query.
 * @return          Number of bits left on buffer to read/write.
 */
int bitPackerBitsAvailable( BitPacker * packer );

/*!
 * @brief Clears the bit packer state and clears the buffer used by the bit packer all to 0.
 *
 * @param packer    Pointer to the packer to clear.
 * @return          0 on success, -1 on error.
 */
int bitPackerClear( BitPacker * packer );

/*!
 * @brief Rewinds the position of the bit cursor of the given packer to the begin of the buffer.
 *
 * @note A rewind can not be used to start writing again into the buffer as the write code needs the buffer to 
 *       be all set to 0.
 *
 * @param packer    Pointer to the packer to rewind.
 * return           0 on success, -1 on error.
 */
int bitPackerRewind( BitPacker * packer );

/*!
 * @brief Writes a given number of bytes of the given 16 bit integer value to the buffer. Note that the LSBs of the value are
 *        written if the bit count is smaller than 16.
 *
 * @param packer    Pointer to the packer to use for writing the bits into the buffer.
 * @param value     Value to write.
 * @param bitCount  The number of bits (from LSB) to write.
 * @return          0 on success, -1 on error.
 */
int bitPackerWrite16( BitPacker * packer , uint16_t value , size_t bitCount );

/*!
 * @brief Reads a given number of bytes to the given 16 bit integer value from the buffer. Note that the LSBs of the value are
 *        read if the bit count is smaller than 16.
 *
 * @param packer    Pointer to the packer to use for reading the bits from the buffer.
 * @param value     Pointer to the value the result of the read operation is written to.
 * @param bitCount  The number of bits (from LSB) to read.
 * @return          0 on success, -1 on error.
 */
int bitPackerRead16( BitPacker * packer , uint16_t * target , size_t bitCount );
