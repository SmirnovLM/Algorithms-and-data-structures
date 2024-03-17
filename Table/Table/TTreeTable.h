#pragma once
#include "TreeNode.h"
#include "TTable.h"
#include <stack>

class TTreeTable : public TTable
{
protected:
	PTreeNode pRoot;    // Корень дерева
	PTreeNode* pTmp;    // Указатель на вершину поддерева, в котором храниться наш результат
	PTreeNode pCurrent; // Текущий элемент (Текущее поддерево)
	std::stack<PTreeNode> stack;
	size_t currentPos;

protected:
	void Print(std::ostream& out, PTreeNode tmp) {

	}
	void Draw(PTreeNode tmp, unsigned char level) {

	}
	void DeleteTree(PTreeNode tmp) {

	}

public:
	TTreeTable() : TTable() {
		pCurrent = nullptr;
		pRoot = nullptr;
		pTmp = nullptr;
		currentPos = 0;
	}

	~TTreeTable() {
		DeleteTree(pRoot);
	}

	// Full
	virtual bool IsFull() const override {
		PTreeNode nod = new TreeNode();
		bool isValid = (nod != nullptr);
		delete nod;
		return !isValid;
	}

	//
	virtual PTDatValue FindRecord(TKey key) override {
		PTreeNode pNode = pRoot;
		pTmp = &pRoot;
		efficiency++;
		while (pNode != nullptr) {
			efficiency++;
			if (pNode->GetKey() == key)
				break;
			if (pNode->GetKey() < key)
				pTmp = &(pNode->pRight);
			else
				pTmp = &(pNode->pLeft);
			pNode = *pTmp;
		}
		if (pNode == nullptr)
			SetRetCode(TAB_NO_RECORD);
		else
			SetRetCode(TAB_OK);
		return pNode == nullptr ? nullptr : pNode->GetValue();
	}
	virtual bool InsertRecord(const TKey key, const PTDatValue pVal) override {
		if (IsFull())
		{
			SetRetCode(TAB_FULL);
			return false;
		}
		else if (FindRecord(key) != nullptr) {
			SetRetCode(TAB_REC_DOUBLE);
			return false;
		}
		else {
			SetRetCode(TAB_OK);
			*pTmp = new TreeNode(key, pVal);
			dataCount++;
			return true;
		}
	}
	virtual void DeleteRecord(const TKey key) override {
		if (FindRecord(key) == nullptr)
			SetRetCode(TAB_NO_RECORD);
		else {
			SetRetCode(TAB_OK);
			PTreeNode pNode = *pTmp;
			if (pNode->pRight == nullptr)
				*pTmp = pNode->pLeft;
			else if (pNode->pLeft == nullptr)
				*pTmp = pNode->pRight;
			else {
				PTreeNode pn = pNode->pLeft;
				PTreeNode* ppr = &(pNode->pLeft);
				while (pn->pRight != nullptr) {
					ppr = &(pn->pRight);
					pn = *ppr;
				}
				pNode->value = pn->value;
				pNode->key = pn->key;
				pNode = pn;
				*ppr = pn->pLeft;
				delete pNode;
			}
		}
	}

	// Navigation
	virtual int Reset() {

	}
	virtual int IsTabEnded() const {

	}
	virtual int GoNext() {

	}

	// Gettings
	virtual TKey GetKey() const {

	}
	virtual PTDatValue GetValue() {

	}
};

