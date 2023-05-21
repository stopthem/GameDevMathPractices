using System.Collections;
using System.Collections.Generic;
using CanTemplate.Extensions;
using Unity.Mathematics;
using UnityEngine;

namespace CanTemplate.Utilities
{
    public static class VectorUtilities
    {
        public static float InverseLerp(Vector3 a, Vector3 b, Vector3 value)
        {
            var ab = b - a;
            var av = value - a;
            return Vector3.Dot(av, ab) / Vector3.Dot(ab, ab);
        }

        public static bool GetIntersection(Vector2 line1Start, Vector2 line1End, Vector2 line2Start, Vector2 line2End, out Vector2 intersectionPoint, bool shouldRestrictToSegment = true)
        {
            intersectionPoint = Vector2.zero;
            Vector2 line1Dir = line1Start.GetDir(line1End, false);
            Vector2 line2Dir = line2Start.GetDir(line2End, false);
            // if dot of the line 1 direction perp and line 2 direction is 0, they are parallel.
            if (Vector2.Dot(line1Dir.GetPerp(), line2Dir) == 0)
            {
                Debug.Log("given lines are parallel!");
                return false;
            }

            Vector2 dirFromLine1To2 = line1Start.GetDir(line2Start, false);
            Vector2 line1DirPerp = line1Dir.GetPerp();
            float t = Vector2.Dot(line1DirPerp, dirFromLine1To2) / Vector2.Dot(line1DirPerp, line2Dir);
            if (t is < -1 or > 1 && shouldRestrictToSegment)
            {
                Debug.Log("intersection is not in line segment");
                return false;
            }

            t = Mathf.Abs(t);

            intersectionPoint = line2Start.GetPointInDirection(line2Dir, t);
            return true;
        }

        public static bool GetIntersectionAtPlane(Vector3 lineStartLocation, Vector3 lineEndLocation, Vector3[] planePoints, out Vector3 intersectionPoint)
        {
            intersectionPoint = Vector3.zero;

            Vector3 lineDir = lineStartLocation.GetDir(lineEndLocation, false);

            Vector3 planeAPoint = planePoints[0], planeBPoint = planePoints[1], planeCPoint = planePoints[2];
            Vector3 dirFromBToC = planeBPoint.GetDir(planeCPoint, false);
            Vector3 dirFromBToA = planeBPoint.GetDir(planeAPoint, false);

            Vector3 planeNormal = Vector3.Cross(dirFromBToC, dirFromBToA).normalized;

            if (Vector2.Dot(planeNormal, lineDir) == 0)
            {
                Debug.Log("Given line is parallel to plane!");
                return false;
            }

            float t = Vector3.Dot(planeNormal, lineStartLocation.GetDir(planeAPoint, false)) / Vector3.Dot(planeNormal, lineDir);
            intersectionPoint = lineStartLocation.GetPointInDirection(lineDir, t);
            return true;
        }

        public static bool GetReflection(Vector3 v, Vector3 normal, out Vector3 reflectedVector)
        {
            Vector3 vNormal = v.GetNormal();
            Vector3 normalN = normal.GetNormal();

            float dot = Vector3.Dot(normalN, vNormal) * 2;

            reflectedVector = vNormal - normalN * dot;

            return true;
        }
    }
}