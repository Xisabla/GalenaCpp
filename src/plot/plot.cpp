#include "./plot.h"

bool plot(vector<pair<double, double>> points, int offset, int width, int height) {
    if (points.size() < 1) return false;

    RenderWindow window(VideoMode(width, height), "GalenaCpp - Plot");

    Font font;
    font.loadFromFile("arial.ttf");

    // Find xmin, xmax, ymin, ymax
    double xmin = points[0].first;
    double xmax = points[0].first;
    double ymin = points[0].second;
    double ymax = points[0].second;

    for (auto &p : points)
    {
        if (p.first > xmax) xmax = p.first;
        if (p.first < xmin) xmin = p.first;
        if (p.second > ymax) ymax = p.second;
        if (p.second < ymin) ymin = p.second; 
    }

    // Axis
    window.clear(Color::White);

    RectangleShape xAxis(Vector2f(width - 2 * offset, 3));
    xAxis.setPosition( offset, height - offset);
    xAxis.setFillColor(Color::Black);

    RectangleShape yAxis(Vector2f(height - 2 * offset, 3));
    yAxis.rotate(-90);
    yAxis.setPosition(offset, height - offset);
    yAxis.setFillColor(Color::Black);

    int thickness = 1;

    while (window.isOpen())
    {
        Event event;

        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
            {
                window.close();
                return true;
            }
        }
        
        // Show points
        for(auto &p : points) {
            double x = offset + (p.first - xmin) * (width - 2 * offset) / (xmax - xmin);
            double y = height - offset - (p.second - ymin) * (height - 2 * offset) / (ymax - ymin);

            CircleShape point(thickness);
            point.setPosition(x, y);
            point.setFillColor(Color::Blue);

            window.draw(point);
        }

        // Show graduations 
        int nb = 7;

        for (int i = 0; i < nb; i++)
        {
            RectangleShape axis(Vector2f(height - 2 * offset, 1));
            axis.rotate(-90);
            axis.setFillColor(Color::Black);

            Text text;
            text.setFont(font);
            text.setCharacterSize(14);
            text.setColor(Color::Black);

            double x = offset + (width - offset * 2) * (i + 1) / (nb + 1);
            double y = height - offset * 2 / 3;
            double fx = (xmax - xmin) * (i + 1) / (nb + 1) + xmin;

            cout << xmin << ";" << xmax << endl;

            text.setString(to_string(fx));
            text.setPosition(x, y);
            axis.setPosition(x, height - offset);

            window.draw(axis);
            window.draw(text);
        }

        for (int i = 0; i < nb; i++)
        {
            RectangleShape axis(Vector2f(width - 2 * offset, 1));
            axis.setFillColor(Color::Black);

            Text text;
            text.setFont(font);
            text.setCharacterSize(10);
            text.setColor(Color::Black);

            double x = offset * 2 / 3;
            double y = height - (height - offset * 2) * (i + 1) / (nb + 1) - offset;
            double fy = (ymax - ymin) * (i + 1) / (nb + 1) + ymin;

            text.setString(to_string(fy));
            text.setPosition(x, y);
            axis.setPosition(offset, y);

            window.draw(axis);
            window.draw(text);
        }

        window.draw(xAxis);
        window.draw(yAxis);

        window.display();
    }

    return true;

}

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