using System;
using System.Linq;
using CanTemplate.Extensions;
using CanTemplate.Utilities;
using UnityEngine;

namespace CourseScripts
{
    public class LinePlaneIntersection : MonoBehaviour
    {
        [SerializeField] private Transform[] planePoints;
        [SerializeField] private Transform lineStartPoint;

        private Vector3 _intersectPoint;

        private void Start()
        {
            VectorUtilities.GetIntersectionAtPlane(lineStartPoint.position, lineStartPoint.position.GetPointInDirection(Vector3.down * 100, 1), planePoints.Select(t => t.position).ToArray(), out _intersectPoint);
            Debug.DrawLine(lineStartPoint.position, lineStartPoint.position + Vector3.down * 100, Color.green, Mathf.Infinity);
        }

        private void OnDrawGizmos()
        {
            Debug.Log(_intersectPoint);
            Gizmos.DrawSphere(_intersectPoint, 1f);
        }
    }
}