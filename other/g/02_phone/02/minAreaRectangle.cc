/*

https://leetcode.com/problems/minimum-area-rectangle/

Given a set of points in the xy-plane, determine the minimum area of a rectangle formed from these points, with sides parallel to the x and y axes.

If there isn't any rectangle, return 0.

Example 1:

Input: [[1,1],[1,3],[3,1],[3,3],[2,2]]
Output: 4
Example 2:

Input: [[1,1],[1,3],[3,1],[3,3],[4,1],[4,3]]
Output: 2


Note:

1 <= points.length <= 500
0 <= points[i][0] <= 40000
0 <= points[i][1] <= 40000
All points are distinct.

*/

class Solution {
public:
    int minAreaRect(vector<vector<int>>& points) {
        // x,y2        X,Y2
        // x,y1        X,Y1
        unordered_map<int, vector<int> > rect;
        vector<int> yPoints1, yPoints2, yPoints, xPoints;
        int area = INT_MAX, i, j, k, x, X, xDiff, yDiff;
        for(auto point: points) {
            rect[point[0]].push_back(point[1]);
        }

        for(auto it=rect.begin(); it!=rect.end(); it++) {
            x = it->first;
            yPoints1 = it->second;
            if(yPoints1.size()==1) {
                continue;
            }
            xPoints.push_back(x);
        }

        for(j=0; j<xPoints.size(); j++) {
            x = xPoints[j];
            yPoints1 = rect[x];
            for(k=j+1; k<xPoints.size(); k++) {
                X = xPoints[k];
                yPoints2 = rect[X];

                yPoints.clear();
                for(auto y: yPoints2) {
                    if(find(yPoints1.begin(), yPoints1.end(), y) != yPoints1.end()) {
                        yPoints.push_back(y);
                    }
                }
                sort(yPoints.begin(), yPoints.end());
                if(yPoints.size()>1) {
                    xDiff = abs(x-X);
                    yDiff = yPoints[1]-yPoints[0];
                    for(i=1; i<yPoints.size(); i++) {
                        yDiff = min(yDiff, yPoints[i]-yPoints[i-1]);
                    }
                    area = min(area, xDiff*yDiff);
                }
            }
        }
        return area==INT_MAX ? 0 : area;
    }
};
