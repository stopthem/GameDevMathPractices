using System;
using CanTemplate.Extensions;
using CanTemplate.Input;
using CanTemplate.Utilities;
using DG.Tweening;
using UnityEngine;

namespace CourseScripts
{
    public class Reflection : MonoBehaviour
    {
        [SerializeField] private Transform ball;
        [SerializeField] private Transform verticalLineStart;

        private Vector3 _ballStartPos;

        private void Start()
        {
            _ballStartPos = ball.transform.position;

            InputManager.onTouchTap += _ =>
            {
                ball.position = _ballStartPos;
                var ballPosition = ball.position;
                ball.DOKill();

                var line2StartPos = verticalLineStart.position;
                VectorUtilities.GetIntersection(ballPosition, ballPosition.XY().GetPointInDirection(new Vector2(1, -.2f) * 100, 1)
                    , line2StartPos.XY(), line2StartPos.XY() + Vector2.down * 100, out Vector2 intersectionPoint);

                VectorUtilities.GetReflection(intersectionPoint
                    , line2StartPos.XY().GetPointInDirection(line2StartPos + Vector3.down * 100, 1).GetPerp()
                    , out Vector3 reflectedVector);

                ball.DOPath(new[] { intersectionPoint.ToV3(), reflectedVector.normalized * 10 }, 1f);
            };
        }
    }
}