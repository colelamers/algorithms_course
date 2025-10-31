public class BitPacker {

	public static byte[] pack(String bits) {
		// Get the total number of bits in the input string
		// Calculate how many full bytes (8-bit chunks) we have
		// Calculate the total number of bytes needed
		int bitLength = bits.length();
		int fullBytes = bitLength / 8;
		int remainingBits = bitLength % 8;
		int totalBytes = fullBytes;
		if (remainingBits > 0) {
			totalBytes += 1;
		}

		// Create a byte array with an extra byte at the end to store
		// the length of the last block
		byte[] packed = new byte[totalBytes + 1];

		// Loop through each full 8-bit block and convert it to a byte
		for (int i = 0; i < fullBytes; ++i) {
			String byteString = bits.substring(i * 8, (i + 1) * 8);
			packed[i] = (byte) HelperFunctions.binaryToDecimal(byteString);
		}

		if (remainingBits > 0) {
			// If there are remaining bits, handle the last block
			String lastSegment = bits.substring(fullBytes * 8);
			packed[fullBytes] = (byte) HelperFunctions.binaryToDecimal(lastSegment);
			packed[totalBytes] = (byte) remainingBits;
		}
		else {
			packed[totalBytes] = 8;
		}
		return packed;
	}

	public static String unpack(byte[] bytes) {
		int validBitsInLastByte = bytes[bytes.length - 1];
		StringBuilder unpacked = new StringBuilder();

		// Loop through all bytes except the last two
		for (int i = 0; i < bytes.length - 2; ++i) {
			int u_int = Byte.toUnsignedInt(bytes[i]);
			String bin = HelperFunctions.decimalToBinary(u_int, 8);
			unpacked.append(bin);
		}

		if (bytes.length > 1) {
			int unsignedInt = Byte.toUnsignedInt(bytes[bytes.length - 2]);
			String lastByteBinary = HelperFunctions.decimalToBinary(unsignedInt, 8);
			if (validBitsInLastByte == 8) {
				unpacked.append(lastByteBinary);
			} else {
				unpacked.append(lastByteBinary.substring(8 - validBitsInLastByte, 8));
			}
		}

		return unpacked.toString();
	}
}