using System;
using CanTemplate.Extensions;
using CanTemplate.Utilities;
using UnityEngine;

namespace CourseScripts
{
    public class LineIntersection : MonoBehaviour
    {
        private Vector2 _intersectPoint;

        private void Start()
        {
            Debug.DrawLine(new(1, 4), new(7, 0.5f), Color.red, Mathf.Infinity);
            Debug.DrawLine(Vector2.zero.WithX(5), Vector2.zero.WithY(7), Color.green, Mathf.Infinity);
            VectorUtilities.GetIntersection(new(1, 4), new(7, 0.5f), Vector2.zero.WithX(5), Vector2.zero.WithY(7), out _intersectPoint, true);
        }

        private void OnDrawGizmos()
        {
            Gizmos.DrawSphere(_intersectPoint, .1f);
        }
    }
}