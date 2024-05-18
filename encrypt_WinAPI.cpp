#include <windows.h>
#include <wincrypt.h>
#include <stdio.h>

#pragma comment(lib, "crypt32.lib")

int main()
{
    HCRYPTPROV hProv;
    HCRYPTHASH hHash;
    HCRYPTKEY hKey;
    HANDLE hFile;

    BYTE pbData[] = "this_is_my_plaintext_suck_my_duck_17201452152172161521521742_Okoonzz";
    DWORD dwDataLen = sizeof(pbData) - 1;  // Size of the plaintext data without null terminator
    DWORD blockSize = 16;  // AES block size is 16 bytes


    // Calculate the required buffer size for the padded plaintext
    DWORD dwPaddedLen = dwDataLen + (blockSize - (dwDataLen % blockSize));
    BYTE* pbPaddedData = new BYTE[dwPaddedLen + blockSize];  // Allocate enough space for padding
    memcpy(pbPaddedData, pbData, dwDataLen);

    // Add padding
    DWORD paddingSize = blockSize - (dwDataLen % blockSize);
    for (DWORD i = 0; i < paddingSize; ++i) {
        pbPaddedData[dwDataLen + i] = (BYTE)paddingSize;
    }
    dwDataLen += paddingSize;  // Update the data length to include the padding

    DWORD dwBufLen = dwDataLen;  // Buffer length for encrypted data, same as padded plaintext size
    DWORD dwBytesWritten = 0;

    //https://learn.microsoft.com/en-us/windows/win32/api/wincrypt/nf-wincrypt-cryptacquirecontexta
    // Acquire a cryptographic provider context handle.
    if (!CryptAcquireContext(&hProv, NULL, NULL, PROV_RSA_AES, CRYPT_VERIFYCONTEXT)) {
        printf("CryptAcquireContext failed: %x\n", GetLastError());
        return -1;
    }


    //https://learn.microsoft.com/en-us/windows/win32/api/wincrypt/nf-wincrypt-cryptcreatehash
    // Create an empty hash object.
    if (!CryptCreateHash(hProv, CALG_SHA_256, 0, 0, &hHash)) {
        printf("CryptCreateHash failed: %x\n", GetLastError());
        CryptReleaseContext(hProv, 0);
        return -1;
    }

    //https://learn.microsoft.com/en-us/windows/win32/api/wincrypt/nf-wincrypt-crypthashdata
    // Hash the password.
    if (!CryptHashData(hHash, (BYTE*)"hey_this_is_my_key", 18, 0)) {
        printf("CryptHashData failed: %x\n", GetLastError());
        CryptDestroyHash(hHash);
        CryptReleaseContext(hProv, 0);
        return -1;
    }

    //https://learn.microsoft.com/en-us/windows/win32/api/wincrypt/nf-wincrypt-cryptgethashparam
    //Get value hash
    BYTE pbDataHash[32];
    DWORD pdwDataLen = 32;
    if (!CryptGetHashParam(hHash, HP_HASHVAL, pbDataHash, &pdwDataLen, 0)) {
        printf("CryptGetHashParam failed: %x\n", GetLastError());
        system("pause");
        return -1;
    }

    printf("SHA-256 Hash: ");
    for (DWORD i = 0; i < pdwDataLen; i++) {
        printf("%02x", pbDataHash[i]);
    }

    printf("\n");

    // Derive a key from the hash object.
    if (!CryptDeriveKey(hProv, CALG_AES_256, hHash, CRYPT_EXPORTABLE, &hKey)) {
        printf("CryptDeriveKey failed: %x\n", GetLastError());
        CryptDestroyHash(hHash);
        CryptReleaseContext(hProv, 0);
        return -1;
    }


    //https://learn.microsoft.com/en-us/windows/win32/api/wincrypt/nf-wincrypt-cryptderivekey
    //change mode, default CBC
    //DWORD mode = CRYPT_MODE_ECB;
    //if (!CryptSetKeyParam(hKey, KP_MODE, (BYTE*)&mode, 0)) {
    //    printf("CryptSetKeyParam failed: %x\n", GetLastError());
    //    CryptDestroyKey(hKey);
    //    CryptDestroyHash(hHash);
    //    CryptReleaseContext(hProv, 0);
    //    return -1;
    //}


    // Set the IV.
    BYTE pbIV[17] = "capture_the_flag";
    if (!CryptSetKeyParam(hKey, KP_IV, pbIV, 0)) {
        printf("CryptSetKeyParam failed: %x\n", GetLastError());
        CryptDestroyKey(hKey);
        CryptDestroyHash(hHash);
        CryptReleaseContext(hProv, 0);
        return -1;
    }

    // Encrypt the data.
    if (!CryptEncrypt(hKey, 0, TRUE, 0, pbPaddedData, &dwDataLen, dwPaddedLen + blockSize)) {
        printf("CryptEncrypt failed: %x\n", GetLastError());
        delete[] pbPaddedData;
        CryptDestroyKey(hKey);
        CryptDestroyHash(hHash);
        CryptReleaseContext(hProv, 0);
        return -1;
    }

    // Open a file to write the encrypted data.
    hFile = CreateFileA("encrypted_data.enc", GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
    if (hFile == INVALID_HANDLE_VALUE) {
        printf("CreateFile failed: %x\n", GetLastError());
        delete[] pbPaddedData;
        CryptDestroyKey(hKey);
        CryptDestroyHash(hHash);
        CryptReleaseContext(hProv, 0);
        return -1;
    }

    // Write the encrypted data to the file.
    if (!WriteFile(hFile, pbPaddedData, dwDataLen, &dwBytesWritten, NULL)) {
        printf("WriteFile failed: %x\n", GetLastError());
        delete[] pbPaddedData;
        CloseHandle(hFile);
        CryptDestroyKey(hKey);
        CryptDestroyHash(hHash);
        CryptReleaseContext(hProv, 0);
        return -1;
    }

    // Clean up.
    delete[] pbPaddedData;
    CloseHandle(hFile);
    CryptDestroyKey(hKey);
    CryptDestroyHash(hHash);
    CryptReleaseContext(hProv, 0);

    printf("Encryption successful. Encrypted data written to 'encrypted_data.enc'.\n");
    return 0;
}
