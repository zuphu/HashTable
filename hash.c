/*
  Get the hash value of character array.
  Courtesy of:
  http://www.sparknotes.com/cs/searching/hashtables/section3.rhtml
  Parameters:
  table_size *hashtable: a number for modulo arithmetic
  char* str: the string to hash
*/
unsigned int hash(int table_size, char *str)
{
  unsigned int hashval;
    
  /* we start our hash out at 0 */
  hashval = 0;

  /* for each character, we multiply the old hash by 31 and add the current
   * character.  Remember that shifting a number left is equivalent to 
   * multiplying it by 2 raised to the number of places shifted.  So we 
   * are in effect multiplying hashval by 32 and then subtracting hashval.  
   * Why do we do this?  Because shifting and subtraction are much more 
   * efficient operations than multiplication.
   */
  for(; *str != '\0'; str++) hashval = *str + (hashval << 5) - hashval;

  /* we then return the hash value mod the hashtable size so that it will
   * fit into the necessary range
   */
  return hashval % table_size;
}
