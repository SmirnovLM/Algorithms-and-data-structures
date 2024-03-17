#pragma once
#include "TTabRecord.h"

// ���� ������
class TreeNode;
using PTreeNode = TreeNode*; // ��������� �� ���� ������

class TreeNode: public TTabRecord
{
protected:
	PTreeNode pLeft;  // ����� �����
	PTreeNode pRight; // ������ �����

public:
	TreeNode(TKey key = "", PTDatValue value = nullptr, PTreeNode left = nullptr, PTreeNode right = nullptr) :
		TTabRecord(key, value), pLeft(left), pRight(right)
		{}

	PTreeNode GetPLeft() const { return pLeft; }
	PTreeNode GetPRight() const { return pRight; }

	virtual PTDatValue GetCopy() override {
		PTreeNode tmp = new TreeNode(key, value->GetCopy());
		return tmp;
	}
	friend class TTreeTable;
};

