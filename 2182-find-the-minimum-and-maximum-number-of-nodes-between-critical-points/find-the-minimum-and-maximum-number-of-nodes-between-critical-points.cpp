class Solution {
public:
    vector<int> nodesBetweenCriticalPoints(ListNode* head) {
        ListNode* prev = head;
        ListNode* curr = head->next;
        int index = 1;
        int first = -1;
        int last = -1;
        int minDist = INT_MAX;
        while (curr && curr->next) {
            ListNode* nxt = curr->next;
            bool isCritical =
                (curr->val > prev->val && curr->val > nxt->val) ||
                (curr->val < prev->val && curr->val < nxt->val);
            if (isCritical) {
                if (first == -1) {
                    first = index;
                } else {
                    minDist = min(minDist, index - last);
                }
                last = index;
            }
            prev = curr;
            curr = nxt;
            index++;
        }
        if (first == -1 || first == last)
            return {-1, -1};
        return {minDist, last - first};
    }
};