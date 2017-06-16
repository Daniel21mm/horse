#include <iostream>
#include <vector>
#include <queue>


struct Point
{
    int x;
    int y;
    Point(int x, int y):x(x),y(y){}

};

using Matrix = std::vector< std::vector < int > >;
using Queue = std::queue < Point >;

void printLine(const char* text)
{
    std::cout << text << std::endl;
}

void printMatrix(Matrix& m)
{
    for(auto& i : m)
    {
        for( auto& j : i)
        {
            std::cout << j << " ";
        }
        std::cout << std::endl;
    }
}

bool isValidityOfCoord(Point p, Matrix& map)
{
    if(  ( p.x >= 0 ) &&  ( p.x < map.size() ) && ( p.y >= 0 ) && ( p.y < map.size())   )
        return true;
    else
        return false;

}

bool isTheMatrixFill(Matrix& m)
{
    for(auto& i : m)
    {
        for( auto& j : i)
        {
            if( j == 0 )
                return false;  // если обнаружена точка на поле равная нулю, то в матрице еще есть не заполеные точки
        }
    }

    return true; // если таких не встретилось, то матрица заполенена
}

void tryPushPoint(Matrix& map, Queue& queuePoints, Point currentPoint )
{
    if( isValidityOfCoord(currentPoint,map) && ( map[currentPoint.x][currentPoint.y] == 0 ) ) // доверяем ленивым вычислениям в С++
    {
        // если точка в допустимой области и не посещене ранее то увеличиваем значение в ней на 1 и добавляем в очередь
        map[ currentPoint.x ][ currentPoint.y ] =  map[ queuePoints.front().x ][ queuePoints.front().y ] + 1;
        queuePoints.push(currentPoint);
    }

}

void iteratingOverTheMap( Matrix& map, Queue& queuePoints )
{
    // обходим текущую точку во всех направлениях и после убераем из очереди
    int x( queuePoints.front().x ), y( queuePoints.front().y );

    tryPushPoint( map, queuePoints, Point ( x + 1, y + 2 ) );
    tryPushPoint( map, queuePoints, Point ( x + 1, y - 2 ) );
    tryPushPoint( map, queuePoints, Point ( x + 2, y + 1 ) );
    tryPushPoint( map, queuePoints, Point ( x + 2, y - 1 ) );
    tryPushPoint( map, queuePoints, Point ( x - 1, y + 2 ) );
    tryPushPoint( map, queuePoints, Point ( x - 1, y - 2 ) );
    tryPushPoint( map, queuePoints, Point ( x - 2, y + 1 ) );
    tryPushPoint( map, queuePoints, Point ( x - 2, y - 1 ) );

    queuePoints.pop();

}

void tryToMakeIterate(Matrix& map, Queue& queuePoints)
{
    if( !isTheMatrixFill( map ) )
    {
        iteratingOverTheMap( map, queuePoints );
        if( !queuePoints.empty() )
            tryToMakeIterate( map, queuePoints );
        else
            printLine("Полностью заолнить карту конем невозможно. Последняя конфигурация:");
    }
    else
        printLine("Поле заполнено конем:");

}

int main()
{
    int sizeMatrix(0);

    while(sizeMatrix <= 4)
    {
        printLine("Введите размер поля ( более четырех ):");

        std::cin >> sizeMatrix;
    }

    Matrix map(sizeMatrix);
    for(auto& i : map)
    {
        i.resize(sizeMatrix);
    }


    int cordX,cordY;
    do
    {
        printLine("Введите значение координат Х и У: ");
        std::cin >> cordX >> cordY;
    }
    while( !isValidityOfCoord( Point( cordX, cordY ), map ) );

    Queue queuePoints;
    queuePoints.push( Point( cordX ,cordY )); // добавляем в очередь первую точку
    map[ cordX ][ cordY ] = 1;  // первую точку на карте отмечаем еденицей

    printLine("Начальное состояние поля:");
    printMatrix( map );

    tryToMakeIterate( map, queuePoints );
    printMatrix( map );


}




