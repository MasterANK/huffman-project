# Huffman Compression and Decompression
This Project implements a **Huffman Tree based file Compression** which is a **lossless file Compression method**. the program converts the set of input data in a stream of bits based on your data rather than ecnoding it in the standard ASCII format. This results in reducing the total file size by **compression frequently occuring characters.**

# Feature
- _**Efficient File Comphresion**_ : Lossless Efficient File Compression with ~50% file size reduction.
- _**Graphical Representation**_ : Give a Visual Representation of the generated Huffman Tree.
- _**Lighweight**_ : Simple Command Line interface
- _**File System Integration**_ : Allow user to Compression there files and automatically generate the Compressed file

# Dev Team
| Ankit Aggarwal | ([@MasterANK](https://github.com/MasterANK)) |
|-|-|

# Data Structures Used:
1. ### Unordered Map:
             - Used for frequency calculation of each character
             - Used for mapping encoded values for each character
2. ### Queue :
             - Used to implement a Min Heap for Creating the Huffman Tree
3. ### Tree :
             - User generated Data struture used to make Huffman Tree.
4. ### Vectors :
             - Used to implement a Min Heap in relation to Queue.

# Contribution 
Contributions to this project are welcome! To contribute:
1. Fork the repository.
2. Create a new branch (git checkout -b feature-branch).
3. Make your changes and commit them (git commit -m "Added feature").
4. Push the changes (git push origin feature-branch).
5. Submit a pull request.
