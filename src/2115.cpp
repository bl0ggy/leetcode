#include "common.h"

class Solution {
  public:
    vector<string> findAllRecipes(vector<string> &recipes, vector<vector<string>> &ingredients, vector<string> &supplies) {
        vector<string> ans;
        unordered_map<string, bool> doable;
        unordered_map<string, int> recipeNameToId;
        for (auto &s : supplies) {
            doable[s] = true;
        }
        for (int i = 0; i < recipes.size(); i++) {
            recipeNameToId[recipes[i]] = i;
        }

        for (auto &recipe : recipes) {
            unordered_set<string> visited;
            checkRecipe(recipe, visited, doable, recipeNameToId, ingredients);
            if (doable[recipe]) {
                ans.push_back(recipe);
            }
        }

        return ans;
    }

    void checkRecipe(string &recipe, unordered_set<string> &visited, unordered_map<string, bool> &doable, unordered_map<string, int> &recipeNameToId, vector<vector<string>> &ingredients) {
        if (doable.contains(recipe)) {
            return;
        }

        if (!recipeNameToId.contains(recipe) || visited.contains(recipe)) {
            doable[recipe] = false;
            return;
        }
        visited.insert(recipe);

        for (auto &ingredient : ingredients[recipeNameToId[recipe]]) {
            checkRecipe(ingredient, visited, doable, recipeNameToId, ingredients);
            if (!doable[ingredient]) {
                doable[recipe] = false;
                return;
            }
        }

        doable[recipe] = true;
    }
};

int main() {
    TestSuite<vector<string>, vector<string>, vector<vector<string>>, vector<string>> testSuite("Find all recipes", "recipes", "ingredients", "supplies");
    testSuite.addTestCases({
        // Original test cases
        {
            {"bread"},
            {"bread"},
            {{"yeast", "flour"}},
            {"yeast", "flour", "corn"},
        },
        {
            {"bread", "sandwich"},
            {"bread", "sandwich"},
            {{"yeast", "flour"}, {"bread", "meat"}},
            {"yeast", "flour", "meat"},
        },
        {
            {"bread", "sandwich"},
            {"bread", "sandwich"},
            {{"yeast", "flour"}, {"bread", "meat"}},
            {"yeast", "flour", "meat"},
        },
        // Submission test cases
        // My test cases
        {
            // stupid cases, recipes can depend on each other, but in that case they're not doable...
            {},
            {"a", "b"},
            {{"b"}, {"a"}},
            {"c"},
        },
        {
            {},
            {"a", "b", "c"},
            {{"b"}, {"c"}, {"a"}},
            {"d"},
        },
    });

    Main main;
    main.runTests(&Solution::findAllRecipes, testSuite);
}
