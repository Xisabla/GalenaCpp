#include "./plot.h"

// points = points to plot
// lines = draw lines between points instead of just ploting points (that are circles)
// loop = if lines, loop tell that there should be a line between points[0] and points[points.size() - 1]
bool plot_points(vector<pair<double, double>> points, bool lines, bool loop) {

    RenderWindow window(VideoMode(500, 300), "GalenaCpp - Plot");

    while(window.isOpen()) {
        Event event;

        while(window.pollEvent(event)) {
            if(event.type == Event::Closed) {
                window.close();
                return true;
            }
        }

        if(lines) {
            for(int i = 0; i < points.size() - 1; i++) {
                auto a = points[i];
                auto b = points[i + 1];

                Vertex line[] = {
                    Vertex(Vector2f(a.first, a.second)),
                    Vertex(Vector2f(b.first, b.second))
                };

                window.draw(line, 2, Lines);
                window.display();
            }

            if(loop) {
                auto a = points[points.size() - 1];
                auto b = points[0];

                Vertex line[] = {
                    Vertex(Vector2f(a.first, a.second)),
                    Vertex(Vector2f(b.first, b.second))};

                window.draw(line, 2, Lines);
                window.display();
            }
        } else {
            for(auto &point : points) {
                CircleShape pt(1);
                pt.setPosition(point.first, point.second);

                window.draw(pt);
                window.display();
            }
        }

        window.display();
        // sleep(milliseconds(1000));
    }


    return true;

}