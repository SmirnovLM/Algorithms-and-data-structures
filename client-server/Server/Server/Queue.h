#pragma once
template <class T>
class Queue {
private:
	T* _data;
	size_t _size;       // ����� ������ �������
	size_t _firstIndex; // ����� � ������� - ������ ������� ������
	size_t _lastIndex;  // ����� � ������� - ���� �������� ������
	size_t _countElem;  // ���������� �������� � �������

public:
	Queue(const Queue&) = delete;
	Queue& operator=(const Queue&) = delete;

	Queue(size_t size = 10) : _size(size) {
		_data = new T[_size];
		_firstIndex = 0;
		_lastIndex = 0;
		_countElem = 0;
	}

	bool Push(const T& elem) {
		if (!IsFull()) {
			_data[_lastIndex] = elem;
			_lastIndex = (_lastIndex + 1) % _size;
			_countElem++;
			return true;
		}
		return false;
	}

	bool PriorityPush(const T& elem) {
		if (!IsFull()) 
		{
			int n = 0;

			if (_countElem == 0) {
				_data[n] = elem;
				_lastIndex = (_lastIndex + 1) % _size;
				_countElem++;
				return true;
			}

			if (_countElem > 0) 
			{
				if (_firstIndex < _lastIndex) {
					n = _lastIndex - 1;
					while (n != _firstIndex - 1) {
						if (elem > _data[n]) {
							_data[n + 1] = _data[n];
							n--;
						}
						else
							break;
					}
					n++;
					_data[n] = elem;
					_lastIndex = (_lastIndex + 1) % _size;
					_countElem++;
					return true;
				}

				if (_firstIndex > _lastIndex) {
					n = _firstIndex;
					while (n != _size) {
						if (_data[n] > elem) {
							_data[n - 1] = _data[n];
							n++;
						}
						else
							break;
					}
					n--;
					_data[n] = elem;
					_firstIndex--;
				}
			}
		}
		return false;
	}

	// ������ ��
	bool IsEmpty() {
		return _countElem == 0;
	}
	// ������ ��
	bool IsFull() {
		return _countElem == _size;
	}

	// ������� 1-�� ������ �� ������� � ������ ���
	T Pop() {
		const T& elem = _data[_firstIndex];
		_firstIndex = (_firstIndex + 1) % _size;
		_countElem--;
		return elem;
	}

	// ������� 1-�� ������� �� ������� ��� ��� ��������
	const T Top() const {
		const T& elem = _data[_firstIndex];
		return elem;
	}
};

