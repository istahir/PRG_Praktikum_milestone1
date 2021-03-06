#include "visualcrypt.h"

/*The following is an encryption function that generates a new slide (folie)
from a given image (bild) and a key (schluessel).
        Arguments:
        - 2d vector bild;
        - 2d vector schluessel;
        Returns:
        - 2d vector folie.
*/
vector<vector <int>> encode(
    vector <vector <int> > bild,
    vector <vector <int> > schluessel){
        // Initialize a vector of folie
        vector < vector<int> > folie;

        for (int i=0; i < bild.size(); i++){
            folie.resize( bild.size()*2 );
            for (int j=0; j < bild[i].size(); j++){

                if ((bild[i][j]==1) && (schluessel[i*2][j*2] == 1)){

                    folie[i*2].insert( folie[i*2].end(), b[0].begin(), b[0].end());
                    folie[i*2+1].insert( folie[i*2+1].end(), b[1].begin(), b[1].end());

                    cout << "Block b was inserted in folie " << i*2 << i*2+1 << endl;

                } else if ((bild[i][j]==0) && (schluessel[i*2][j*2] == 1)){

                    folie[i*2].insert( folie[i*2].end(), a[0].begin(), a[0].end());
                    folie[i*2+1].insert( folie[i*2+1].end(), a[1].begin(), a[1].end());

                    cout << "Block a was inserted in folie " << i*2 << i*2+1 << endl;

                } else if ((bild[i][j]==1) && (schluessel[i*2][j*2] == 0)){

                    folie[i*2].insert( folie[i*2].end(), a[0].begin(), a[0].end());
                    folie[i*2+1].insert( folie[i*2+1].end(), a[1].begin(), a[1].end());

                    cout << "Block a was inserted in folie " << i*2 << i*2+1 << endl;

                } else if ((bild[i][j]==0) && (schluessel[i*2][j*2] == 0)){

                    folie[i*2].insert( folie[i*2].end(), b[0].begin(), b[0].end());
                    folie[i*2+1].insert( folie[i*2+1].end(), b[1].begin(), b[1].end());

                    cout << "Block b was inserted in folie " << i*2 << i*2+1 << endl;

                }

            }

        }

        return folie;

    }

/*The following is a decryption function that generates an image (bild) from an
encrypted slide (folie) and a key (schluessel).
        Arguments:
        - 2d vector folie;
        - 2d vector schluessel;
        Returns:
        - 2d vector bild.
*/
vector<vector <int>> decode(
    vector <vector <int> > folie,
    vector <vector <int> > schluessel){
        // Initialize a vector of folie
        vector < vector<int> > bild;

        for (int i=0; i < folie.size(); i+=2){
            bild.resize( folie.size()/2 );

            for (int j=0; j < folie[i].size(); j+=2){

                if ((folie[i][j]==1) && (schluessel[i][j] == 1)){

                    bild[i/2].insert( bild[i/2].end(), 0);

                    cout << "Block 0 was inserted in bild " << i/2 << j/2 << endl;

                } else if ((folie[i][j]==1) && (schluessel[i][j] == 0)){

                    bild[i/2].insert( bild[i/2].end(), 1);

                    cout << "Block 1 was inserted in bild " << i/2 << j/2 << endl;

                } else if ((folie[i][j]==0) && (schluessel[i][j] == 1)){

                    bild[i/2].insert( bild[i/2].end(), 1);

                    cout << "Block 1 was inserted in bild " << i/2 << j/2 << endl;

                } else if ((folie[i][j]==0) && (schluessel[i][j] == 0)){

                    bild[i/2].insert( bild[i/2].end(), 0);

                    cout << "Block 0 was inserted in bild " << i/2 << j/2 << endl;

                }

            }

        }

        return bild;

    }


/*The following is a function that overlays two images (bild1, bild2).
        Arguments:
        - 2d vector bild1;
        - 2d vector bild2;
        Returns:
        - 2d vector overlayImage.
*/
vector<vector <int>> overlay(
    vector <vector <int> > bild1,
    vector <vector <int> > bild2){

        // Initialize a vector of overlayImage
        vector < vector<int> > overlayImage;

        // For images of unequal sizes determine maxLength and maxWidth:
        // Resize smaller image and fill missing cells with 0s.
        size_t maxLength;
        if ( bild1.size() > bild2.size() ){ //rows: bild1 > bild2
            maxLength = bild1.size();
            cout << "maxLength=bild1" << endl;
            // Add missing rows to smaller image and fill cells with 0s:
            // create a row with bild2[0].size() entries and push_back it maxLength.size times
            vector <int> row;
            row.resize(bild2[0].size(), 0);
            for (int i=0; i < maxLength - bild2.size(); i++){
                bild2.push_back(row);
            }

            // Print out new bild2
            cout << "New bild2:" << endl;
            for (int it=0; it < bild2.size(); it++){
                for (vector<int>::iterator i = bild2[it].begin(); i != bild2[it].end(); ++i){
                    cout << ' ' << *i;
                    }
                    cout << '\n' << endl;
            }


        } else if ( bild1.size() < bild2.size() ){
            maxLength = bild2.size();
            cout << "maxLength=bild2" << endl;
            // Add missing rows to smaller image and fill cells with 0s:
            // create a row with bild2[0].size() entries and push_back it maxLength.size times
            vector <int> row;
            row.resize(bild1[0].size(), 0);
            for (int i=0; i < maxLength - bild1.size(); i++){
                bild1.push_back(row);
            }

            // Print out new bild1
            cout << "New bild1:" << endl;
            for (int it=0; it < bild1.size(); it++){
                for (vector<int>::iterator i = bild1[it].begin(); i != bild1[it].end(); ++i){
                    cout << ' ' << *i;
                    }
                    cout << '\n' << endl;
            }
        } else {
            maxLength = bild1.size();
        }

        size_t maxWidth;
        if (bild1[0].size() > bild2[0].size() ){
            maxWidth = bild1[0].size();
            cout << "bild1[0] size: " << bild1[0].size() << ", " << "bild2[0] size: " << bild2[0].size() << endl;
            cout << "maxWidth=bild1" << endl;
            // Add missing entries to bild2, row by row
            for (int i=0; i < bild2.size(); i++){
                bild2[i].resize(maxWidth, 0);
            }
        } else {
            maxWidth = bild2[0].size();
            cout << "bild1[0] size: " << bild1[0].size() << ", " << "bild2[0] size: " << bild2[0].size() << endl;
            cout << "maxWidth=bild2" << endl;
            // Add missing entries to bild1, row by row
            for (int i=0; i < bild1.size(); i++){
                bild1[i].resize(maxWidth, 0);
            }
        }

        // Compare images:
        for (int i=0; i<bild1.size(); i++){
            overlayImage.resize( maxLength );
            for (int j=0; j < maxWidth; j++){

                bool cmp = bild1[i][j] == bild2[i][j];
                cout << "Bild1: " << bild1[i][j] << ", " << "Bild 2: " << bild2[i][j] << ", " << "Compare: " << cmp << endl;
                //cout << bild1[0].size() << endl;

                if (bild1[i][j] == bild2[i][j]){

                    overlayImage[i].insert( overlayImage[i].end(), bild1[i][j]);
                    cout << "Block " << bild1[i][j] << " was inserted in overlayImage " << i << j << endl;

                } else if (bild1[i][j] != bild2[i][j]){

                    overlayImage[i].insert( overlayImage[i].end(), 1);
                    cout << "Block 1 was inserted in overlayImage " << i << j << endl;

                }
            }
        }

        return overlayImage;
    }


/*The following is a function that generates a random matrix of a given size.
        Arguments:
        - x number of rows;
        - y number of columns;
        Returns:
        - 2d vector randMatrix.
*/
vector<vector <int>> genMatrix(int x, int y){
    vector < vector<int> > randMatrix;
    vector <int> helpVec;
    for (int i=0; i<x; i++){
        for (int j=0; j<y; j++){
            int a=rand()%2;
            helpVec.push_back(a);
        }
        randMatrix.push_back(helpVec);
        helpVec.clear();
    }
    return randMatrix;
}


/*The following is a function that generates a random key (schluessel) for an image of a given size.
        Arguments:
        - x number of rows in the image;
        - y number of columns in the image;
        Returns:
        - 2d vector schluessel.
*/
vector<vector <int>> genKey(int x, int y){
    vector < vector<int> > schluessel;
    schluessel.resize(x*2);

    vector < vector<int> > randomMatrix = genMatrix(x,y);

    for (int i=0; i < randomMatrix.size(); i++){
        for (int j=0; j < randomMatrix[i].size(); j++){

            if (randomMatrix[i][j]==1){

                schluessel[i*2].insert( schluessel[i*2].end(), b[0].begin(), b[0].end());
                schluessel[i*2+1].insert( schluessel[i*2+1].end(), b[1].begin(), b[1].end());

                cout << "Block b was inserted in folie " << i*2 << i*2+1 << endl;

            } else if (randomMatrix[i][j]==0){

                schluessel[i*2].insert( schluessel[i*2].end(), a[0].begin(), a[0].end());
                schluessel[i*2+1].insert( schluessel[i*2+1].end(), a[1].begin(), a[1].end());

                cout << "Block a was inserted in folie " << i*2 << i*2+1 << endl;

            }
        }
    }

    return schluessel;
}


/*The following is a procedure that prints a vector.
        Arguments:
        - vector
        Returns:
        - prints out a vector.
*/
void printVec(vector <int> printedVector, string name){
    cout << name << ": " << endl;
    for (vector<int>::iterator i = printedVector.begin(); i != printedVector.end(); ++i){
        cout << ' ' << *i;
    }
}

/*The following is a procedure that prints a matrix.
        Arguments:
        - matrix
        Returns:
        - prints out a matrix.
*/
void printMat(vector <vector <int> > printedMatrix, string name){
    cout << '\n' << name << ": " << endl;
    for (int it=0; it < printedMatrix.size(); it++){
        for (vector<int>::iterator i = printedMatrix[it].begin(); i != printedMatrix[it].end(); ++i){
            cout << ' ' << *i;
            }
            cout << '\n' << endl;
    }
}
