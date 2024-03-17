#pragma once
#include "TTabRecord.h"

// Узел Дерева
class TreeNode;
using PTreeNode = TreeNode*; // Указатель на Узел Дерева

class TreeNode: public TTabRecord
{
protected:
	PTreeNode pLeft;  // Левый Сосед
	PTreeNode pRight; // Правый сосед

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

