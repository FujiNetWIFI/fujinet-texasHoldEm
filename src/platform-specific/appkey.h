/**
 * @brief   App Key Functions
 * @author  Oscar Fowler, Thomas Cherryhomes, Eric Carr
 * @license gpl v. 3
 */

#ifndef APPKEY_H
#define APPKEY_H

#define MAX_APPKEY_LEN 64

/**
 * @brief Read a key; data is NUL-terminated, and empty on failure
 * @param creator_id Key creator ID: ($0000-$FFFF)
 * @param app_id The App ID ($00-$FF)
 * @param key_id The Key ID ($00-$FF)
 * @param data Output buffer, MAX_APPKEY_LEN+1 bytes
 */
void read_appkey(unsigned int creator_id, unsigned char app_id, unsigned char key_id, char *data);

/**
 * @brief Write a key
 * @param creator_id Key creator ID: ($0000-$FFFF)
 * @param app_id The App ID ($00-$FF)
 * @param key_id The Key ID ($00-$FF)
 * @param data String to write (MAX_APPKEY_LEN chars max)
 */
void write_appkey(unsigned int creator_id, unsigned char app_id, unsigned char key_id, const char *data);

#endif /* APPKEY_H */
