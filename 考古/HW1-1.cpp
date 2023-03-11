#include <iostream>
#include <vector>

using namespace std;

void Print(long long a[], int n)
{
    for (int i = 0; i < n; i++)
    {
        cout << a[i] << " ";
    }
    cout << endl;
}
int main()
{
    int n;
    cin >> n;
    int matrix[n][n];
    int k;
    cin >> k;
    long long player[n] = {0};
    int win;
    cin >> win;
    int lose;
    cin >> lose;
    int tie;
    cin >> tie;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            cin >> matrix[i][j];
            if (i != j)
            {
                switch (matrix[i][j])
                {
                case 0:
                    player[i] += lose;
                    break;
                case 1:
                    player[i] += win;
                    break;
                case 2:
                    player[i] += tie;
                    break;
                }
            }
        }
    }
    // Print(player, n);
    for (int i = 0; i < k; i++)
    {
        int p1, p2, operation;
        cin >> p1 >> p2 >> operation;
        p1--;
        p2--;
        switch (matrix[p1][p2])
        {
        case 0:
            player[p1] -= lose;
            player[p2] -= win;
            break;
        case 1:
            player[p1] -= win;
            player[p2] -= lose;
            break;
        case 2:
            player[p1] -= tie;
            player[p2] -= tie;
            break;
        }
        // cout << "after minus: ";
        //Print(player, n);

        switch (operation)
        {
        case 0:
            player[p1] += lose;
            player[p2] += win;
            matrix[p1][p2] = 0;
            matrix[p2][p1] = 1;
            break;
        case 1:
            player[p1] += win;
            player[p2] += lose;
            matrix[p1][p2] = 1;
            matrix[p2][p1] = 0;
            break;
        case 2:
            player[p1] += tie;
            player[p2] += tie;
            matrix[p1][p2] = 2;
            matrix[p2][p1] = 2;
            break;
        }
        /*cout << "after plus: ";
    Print(player, n);
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            cout << matrix[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;*/
        int min = 1 << 30, max = -1;
        for (int i = 0; i < n; i++)
        {
            if (player[i] > max)
                max = player[i];
            if (player[i] < min)
                min = player[i];
        }
        // cout << "max: " << max << " min: " << min << endl;
        cout << max - min << " ";
        // cout << endl;
    }

    return 0;
}