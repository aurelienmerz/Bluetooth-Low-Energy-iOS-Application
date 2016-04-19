#include "bitpacker.h"
#include <string.h>
#include <stdio.h>

int bitPackerInit( BitPacker * packer , uint8_t * buffer , size_t bytesSize )
{
    /* Check arguments: we need a valid pointer to a packer struct and a pointer to the buffer. */
    if ( ! packer || ! buffer ) return -1;
    
    /* Initialize the bit packer attributes. */
    packer->bitPosition = 0;
    packer->bitSize = bytesSize * 8;
    packer->data = buffer;
    
    /* We have to set all elements of the buffer to 0... */
    return bitPackerClear( packer );
}

int bitPackerBitsAvailable( BitPacker * packer )
{
    /* Check arguments: we need a valid pointer to a packer struct. */
    if ( ! packer ) return -1;

    /* calculate and return the number of bits left. */
    return (int)packer->bitSize - (int)packer->bitPosition;
}

int bitPackerClear( BitPacker * packer )
{
    /* Check argument: we need a valid pointer to a packer struct and a pointer to the data. */
    if ( ! packer || ! packer->data ) return -1;
    
    /* Set the bit position back to 0 */
    packer->bitPosition = 0;
    
    /* Fill the buffer with 0s. */
    memset( packer->data , 0 , packer->bitSize / 8 );
    
    return 0;
}

int bitPackerRewind( BitPacker * packer )
{
    /* Check argument: we need a valid pointer to a packer struct. */
    if ( ! packer ) return -1;
    
    /* Set the bit position back to 0. */
    packer->bitPosition = 0;
    
    return 0;
}

int bitPackerWrite16( BitPacker * packer , uint16_t value , size_t bitCount )
{
    size_t offset, bitsAvailableAtOffset, bitsToWrite, i;
    int bitsToShiftLeft;
    uint8_t mask = 0;
    
    /* Check arguments: we need a valid pointer to a packer struct, the buffer must be big enaugh to hold the additional data and 
       we certainly can not write more than 16 bytes. */
    if ( ! packer || packer->bitPosition + bitCount > packer->bitSize || bitCount > 16 ) return -1;
    
    /* Calculate the byte offset. */
    offset = packer->bitPosition / 8;
    
    /* Calculate how many bits we can save into the actual byte boundary. */
    bitsAvailableAtOffset = ( ( offset + 1 ) * 8 ) - packer->bitPosition;
    
    /* IDetermine the number of bits we actually write during this function call. */
    bitsToWrite = bitCount < bitsAvailableAtOffset ? bitCount : bitsAvailableAtOffset;
    
    /* Calculate the number of bytes we have to shift the value to the left in order to write it to the buffer. */
    bitsToShiftLeft = (int)bitsAvailableAtOffset - (int)bitCount;
    
    /* Create the write mask */
    for ( i = 0 ; i < bitsAvailableAtOffset ; ++i ) mask |= 1 << i;

    /* If the shift left value is greater or equal zero, we shift to the left. */
    if ( bitsToShiftLeft >= 0 ) *( packer->data + offset ) |= ( value << bitsToShiftLeft ) & mask;
    
    /* Otherwise we shift the negative value of shift left to the right. */
    else *( packer->data + offset ) |= ( value >> -bitsToShiftLeft ) & mask;
    
    /* Add the number of the written bits to the bit position. */
    packer->bitPosition += bitsToWrite;
    
    /* If we could not write all bits, call the function again with the rest of the bits. */
    if ( bitCount > bitsToWrite ) return bitPackerWrite16( packer , value , bitCount - bitsToWrite );
    
    return 0;
}

int bitPackerRead16( BitPacker * packer , uint16_t * target , size_t bitCount )
{
    size_t offset, bitsAvailableAtOffset, bitsToRead, i;
    int bitsToShiftLeft;
    uint8_t mask = 0;
    
    /* Check arguments: we need a valid pointer to a packer struct and the target, the buffer must be big enaugh to hold the 
       additional data and we certainly can not read more than 16 bytes. */
    if ( ! packer || ! target || packer->bitPosition + bitCount > packer->bitSize || bitCount > 16 ) return -1;
    
    /* Calculate the byte offset. */
    offset = packer->bitPosition / 8;
    
    /* Calculate how many bits we can save into the actual byte boundary. */
    bitsAvailableAtOffset = ( ( offset + 1 ) * 8 ) - packer->bitPosition;
    
    /* IDetermine the number of bits we actually write during this function call. */
    bitsToRead = bitCount < bitsAvailableAtOffset ? bitCount : bitsAvailableAtOffset;
    
    /* Calculate the number of bytes we have to shift the value to the left in order to write it to the buffer. */
    bitsToShiftLeft = (int)bitCount - (int)bitsAvailableAtOffset;
    
    /* Create the write mask */
    for ( i = 0 ; i < bitsAvailableAtOffset ; ++i ) mask |= 1 << i;
    
    /* Set target to 0. */
    *target = 0;
    
    /* If the shift left value is greater or equal zero, we shift to the left. */
    if ( bitsToShiftLeft >= 0 ) *target |= ( *( packer->data + offset ) & mask ) << bitsToShiftLeft;
    
    /* Otherwise we shift the negative value of shift left to the right. */
    else *target |= ( *( packer->data + offset ) & mask ) >> -bitsToShiftLeft;
    
    /* Add the number of the written bits to the bit position. */
    packer->bitPosition += bitsToRead;
    
    /* If we could not write all bits, call the function again with the rest of the bits. */
    if ( bitCount > bitsToRead )
    {
        uint16_t tmp;
        if ( bitPackerRead16( packer , &tmp , bitCount - bitsToRead ) ) return -1;
        *target |= tmp;
    }
    
    return 0;

}
