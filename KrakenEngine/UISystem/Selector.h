#pragma once
#include "ISelectable.h"
#include <vector>
#include <memory>
#include <set>
#include "UIUtilites.h"
#include "Event.h"
#include "CardView.h"

template<class T> 
class Selector
{
public:
	Event<Point, T*> Dragging;
	Event<Point, T*> StartDragging;
	Event<Point, T*> EndDragging;
	Event<Point, T*> Selected;

	void AddSelectable(ISelectable* selectable) {
		_selectables.push_back(selectable);
	}

 	void Update() {
		Point mousePos = UIUtilites::GetLocalMousePosition();
		bool mouseState = GetAsyncKeyState(VK_LBUTTON) & 0x8000;

		ISelectable* top = GetTopSelectable(mousePos);

		if (!_lastMouseState && mouseState) {
			_mouseDownPosition = mousePos;
		}

		if (!_isDragging && (_mouseDownPosition - mousePos).GetMagnitude() >= dragTreshold) {
			StartDragging(mousePos, dynamic_cast<T*>(top));
			_isDragging = true;
		}

		if (_isDragging) {
			Dragging(mousePos - _lastMousePosition, dynamic_cast<T*>(top));
		}

		if (_lastMouseState && mouseState) {
			if (_isDragging) {
				EndDragging(mousePos, &dynamic_cast<T>(*top));
			}
			else {
				top->OnSelected(mousePos);
				Selected(mousePos, &dynamic_cast<T*>(top));
			}
		}

		for (auto selectable : _selectables) {
			bool isInRect = IsInRect(mousePos, selectable->GetRect());
			if (isInRect && !_wasUnderPoint.insert(selectable).second)
			{
				selectable->OnPointEnter(mousePos);
			}
			if (!isInRect && _wasUnderPoint.find(selectable) != _wasUnderPoint.end()) {
				selectable->OnPointExit(mousePos);
				_wasUnderPoint.erase(selectable);
			}
		}

		_lastMouseState = mouseState;
		_lastMousePosition = mousePos;
	}

	ISelectable* GetTopSelectable(Point point) {
		ISelectable* top = _selectables.front();
		for (auto selectable : _selectables) {
			if (IsInRect(point, selectable->GetRect()) && selectable->GetZPosition() > top->GetZPosition()) {
				top = selectable;
			}
		}

		return top;
	}

	void Select(Point point) {
		for (auto selectable : _selectables) {
			if(IsInRect(point,selectable->GetRect()))
				selectable->OnSelected(point);
		}
	}

private:

	std::vector<ISelectable*> _selectables;
	std::set<ISelectable*> _wasUnderPoint;
	std::list<ISelectable*> _currentSelectables;
	bool _lastMouseState;
	Point _mouseDownPosition;
	Point _lastMousePosition;
	float dragTreshold = .1f;
	bool _isDragging;

	bool IsInRect(Point point, Rect rect) {
		return point.x > rect.left && point.x < rect.right && point.y > rect.top && point.y < rect.buttom;
	}
};

