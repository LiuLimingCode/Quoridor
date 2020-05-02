#include "GameAI.h"
#include "GameData.h"
#include "GameGlobal.h"
#include <vector>
#include <cmath>
#include <cstdlib>
#include <ctime>

struct MoveNode {
public:
    
    Order mOrder;
    MoveNode* mParent = nullptr;
    long mUctConst = 0;
    int mNumWins = 0;
    int mNumSims = 0;
    std::vector<MoveNode *> mChildren;
    bool isTerminal = false;

public:
    MoveNode(Order move, MoveNode* parent, long uctConst) {
        mOrder = move;
        mParent = parent;
        mUctConst = uctConst;
    }

    ~MoveNode()
    {
        for (int index = 0; index != mChildren.size(); ++index)
            delete mChildren[index];
    }
    
    bool isLeaf() {
        return mChildren.size() == 0;
    }

    bool isNew(void) {
        return mNumSims == 0;
    }

    // References: 
    // Levente Kocsis, Csaba Szepesva ́ri (2006 ) "Bandit based Monte-Carlo Planning"
    // Peter Auer, Cesa-Bianchi, Fischer (2002) "Finite-time Analysis of the Multiarmed Bandit Problem"
    // Do google search for "monte carlo tree search uct"
    double uct(void) {
        if (mParent == nullptr || mParent->mNumSims == 0) {
            return 0;
        }
        if (mNumSims == 0) {
            return 0;
        }
        return ((double)mNumWins / (double)mNumSims) + sqrt((mUctConst * log(mParent->mNumSims)) / (double)mNumSims);
    }

    double winRate(void) const { 
        return (double)mNumWins / (double)mNumSims;
    }

    MoveNode* maxUCTChild() {
        std::vector<int> maxUCTIndices;
        double maxUCT = 0;
        for (int i = 0; i != mChildren.size(); i++) {
            const double uct = mChildren[i]->uct();
            if (uct > maxUCT) {
                maxUCT = uct;
                maxUCTIndices.clear();
                maxUCTIndices.push_back(i);
            }
            else if (uct == maxUCT) {
                maxUCTIndices.push_back(i);
            }
        }
        srand((unsigned int)time(0));
        const int maxUCTIndex = maxUCTIndices[rand() % maxUCTIndices.size()];
        //const maxUCTIndex = maxUCTIndices[0];
        return mChildren[maxUCTIndex];
    }

    MoveNode* maxWinRateChild() {
        int maxWinRateIndex = 0;
        double maxWinRate = 0;
        for (int i = 0; i != mChildren.size(); i++) {
            if (mChildren[i]->winRate() > maxWinRate) {
                maxWinRate = mChildren[i]->winRate();
                maxWinRateIndex = i;
            }
        }
        return mChildren[maxWinRateIndex];
    }

    MoveNode* maxSimsChild(void) {
        int maxSimsIndex = 0;
        int maxSims = 0;
        for (int i = 0; i != mChildren.size(); i++) {
            if (mChildren[i]->mNumSims > maxSims) {
                maxSims = mChildren[i]->mNumSims;
                maxSimsIndex = i;
            }
        }
        return mChildren[maxSimsIndex];
    }

    void addChild(MoveNode* childNode) {
        mChildren.push_back(childNode);
    }
};


/*struct MonteCarloTreeSearch {

    GameData* game;
    long uctConst;
    MoveNode* root;
    int totalNumOfSimulations = 0;


    MonteCarloTreeSearch(GameData* game, long uctConst) {
        this->game = game;
        this->uctConst = uctConst;
        this->root = new MoveNode(Order(), nullptr, this->uctConst);
    }

    int maxDepth(MoveNode* node) {
        int max = 0;
        for (int i = 0; i < node->mChildren.size(); i++) {
            const int d = this->maxDepth(node->mChildren[i]) + 1;
            if (d > max) {
                max = d;
            }
        }
        return max;
    }

    std::pair<const Order, double> selectBestMove(void) {
        const MoveNode* best = this->root->maxSimsChild();
        return std::make_pair(best->mOrder, best->winRate());
    }

    GameData getSimulationGameAtNode(MoveNode* node) {
        GameData simulationGame = GameData(*game);
        std::vector<Order> stack;

        MoveNode* ancestor = node;
        while (ancestor->mParent != nullptr) {
            stack.push_back(ancestor->mOrder); // moves stacked to a child of root. root's move is not stacked.
            ancestor = ancestor->mParent;
        }

        while (stack.size() > 0) {
            const Order move = stack.back();
            stack.pop_back();
            simulationGame.setOrder(mSelfID, move);
        }
        return simulationGame;
    }

    // also called playout
    void rollout(MoveNode* node) {
        this->totalNumOfSimulations++;
        const GameData simulationGame = this->getSimulationGameAtNode(node);

        // the pawn of this node is the pawn who moved immediately before,
        // put it another way, the pawn who leads to this node right before,
        // i.e. pawn of not turn.
        const nodePawnIndex = simulationGame.pawnIndexOfNotTurn;
        if (simulationGame.winner != = null) {
            node.isTerminal = true;
        }

        // Simulation
        const cacheForPawns = [
        {
        updated: false,
            prev : null,
            next : null,
            distanceToGoal : null
        },
            {
                updated: false,
                prev : null,
                next : null,
                distanceToGoal : null
            }
        ];
        let pawnMoveFlag = false;

        while (simulationGame.winner == = null) {
            if (!cacheForPawns[0].updated) {
                const t = AI.get2DArrayPrevAndNextAndDistanceToGoalFor(simulationGame.pawn0, simulationGame);
                cacheForPawns[0].prev = t[0];
                cacheForPawns[0].next = t[1];
                cacheForPawns[0].distanceToGoal = t[2];
                cacheForPawns[0].updated = true;
            }
            if (!cacheForPawns[1].updated) {
                const t = AI.get2DArrayPrevAndNextAndDistanceToGoalFor(simulationGame.pawn1, simulationGame);
                cacheForPawns[1].prev = t[0];
                cacheForPawns[1].next = t[1];
                cacheForPawns[1].distanceToGoal = t[2];
                cacheForPawns[1].updated = true;
            }

            const pawnOfTurn = simulationGame.pawnOfTurn;
            const pawnIndexOfTurn = simulationGame.pawnIndexOfTurn;
            // heuristic:
            // With a certain probability, move pawn to one of the shortest paths.
            // And with the rest probability, half place a wall randomly / half move pawn randomly.
            // This heuristic shorten the time taken by rollout phase.
            if (Math.random() < 0.7) {
                // move pawn to one of shortest paths
                pawnMoveFlag = false;
                const next = cacheForPawns[pawnIndexOfTurn].next;
                const currentPosition = pawnOfTurn.position;
                let nextPosition = next[currentPosition.row][currentPosition.col];
                if (nextPosition == = null) {
                    console.log("really?? already in goal position");
                    throw "already in goal Position...."
                }
                if (AI.arePawnsAdjacent(simulationGame)) {
                    const nextNextPosition = next[nextPosition.row][nextPosition.col];
                    if (nextNextPosition != = null
                        && simulationGame.validNextPositions[nextNextPosition.row][nextNextPosition.col] == = true) {
                        nextPosition = nextNextPosition;
                        cacheForPawns[pawnIndexOfTurn].distanceToGoal -= 2;
                    }
                    else {
                        const nextPositions = AI.chooseShortestPathNextPawnPositionsThoroughly(simulationGame);
                        const _nextPosition = randomChoice(nextPositions);
                        if (_nextPosition.equals(nextPosition)) {
                            cacheForPawns[pawnIndexOfTurn].distanceToGoal -= 1;
                        }
                        else {
                            nextPosition = _nextPosition;
                            cacheForPawns[pawnIndexOfTurn].updated = false;
                        }
                    }
                }
                else {
                    cacheForPawns[pawnIndexOfTurn].distanceToGoal -= 1;
                }
                simulationGame.movePawn(nextPosition.row, nextPosition.col);
            }
            else if (!pawnMoveFlag && pawnOfTurn.numberOfLeftWalls > 0 ) {//&& Math.random() < 0.5
                // place a wall
                // (If a pawn has no wall, this fall in to next else clause so move pawn randomly.
                // So, consuming all wall early gives no advantage, it rather gives a disadvantage)
                const nextMove = AI.chooseProbableNextWall(simulationGame);
                //const nextMove = AI.chooseNextWallRandomly(simulationGame);
                //const nextMove = AI.chooseNextWallWisely(simulationGame);

                if (nextMove != = null) {
                    simulationGame.doMove(nextMove);
                    cacheForPawns[0].updated = false;
                    cacheForPawns[1].updated = false;
                }
                else {
                    console.log("No probable walls possible")
                        pawnMoveFlag = true;
                }
            }
            else {
                // move pawn backwards
                pawnMoveFlag = false;
                //const nextRandomPosition = AI.chooseNextPawnPositionRandomly(simulationGame);
                const prev = cacheForPawns[pawnIndexOfTurn].prev;
                const currentPosition = pawnOfTurn.position;
                let prevPosition = prev[currentPosition.row][currentPosition.col];
                if (prevPosition == = null || !simulationGame.validNextPositions[prevPosition.row][prevPosition.col]) {
                    const prevPositions = AI.chooseLongestPathNextPawnPositionsThoroughly(simulationGame);
                    prevPosition = randomChoice(prevPositions);
                    cacheForPawns[pawnIndexOfTurn].updated = false;
                }
                else {
                    cacheForPawns[pawnIndexOfTurn].distanceToGoal += 1;
                }
                simulationGame.movePawn(prevPosition.row, prevPosition.col);
            }
        }

        // Backpropagation
        let ancestor = node;
        let ancestorPawnIndex = nodePawnIndex;
        while (ancestor != = null) {
            ancestor.numSims++;
            if (simulationGame.winner.index == = ancestorPawnIndex) {
                ancestor.numWins += 1;
            }
            ancestor = ancestor.parent;
            ancestorPawnIndex = (ancestorPawnIndex + 1) % 2;
        }
    }

    void search(int numOfSimulations) {
        const long uctConst = this->uctConst;

        MoveNode* currentNode = this->root;
        const int limitOfTotalNumOfSimulations = this->totalNumOfSimulations + numOfSimulations;
        while (this->totalNumOfSimulations < limitOfTotalNumOfSimulations) {
            // Selection
            if (currentNode->isTerminal) {
                this->rollout(currentNode);
                currentNode = this->root;
            }
            else if (currentNode->isLeaf()) {
                if (currentNode->isNew()) {
                    this->rollout(currentNode);
                    currentNode = this->root;
                }
                else {
                    // Expansion
                    const simulationGame = this->getSimulationGameAtNode(currentNode);
                    let move, childNode;
                    if (simulationGame.pawnOfNotTurn.numberOfLeftWalls > 0) {
                        const nextPositionTuples = simulationGame.getArrOfValidNextPositionTuples();
                        for (let i = 0; i < nextPositionTuples.length; i++) {
                            move = [nextPositionTuples[i], null, null];
                            childNode = new MNode(move, currentNode, uctConst);
                            currentNode.addChild(childNode);
                        }
                        if (simulationGame.pawnOfTurn.numberOfLeftWalls > 0) {
                            const noBlockNextHorizontals = simulationGame.getArrOfProbableValidNoBlockNextHorizontalWallPositions();
                            for (let i = 0; i < noBlockNextHorizontals.length; i++) {
                                move = [null, noBlockNextHorizontals[i], null];
                                childNode = new MNode(move, currentNode, uctConst);
                                currentNode.addChild(childNode);
                            }
                            const noBlockNextVerticals = simulationGame.getArrOfProbableValidNoBlockNextVerticalWallPositions();
                            for (let i = 0; i < noBlockNextVerticals.length; i++) {
                                move = [null, null, noBlockNextVerticals[i]];
                                childNode = new MNode(move, currentNode, uctConst);
                                currentNode.addChild(childNode);
                            }
                        }
                    }
                    else {
                        // heuristic:
                        // If opponent has no walls left,
                        // my pawn moves only to one of the shortest paths.
                        const nextPositions = AI.chooseShortestPathNextPawnPositionsThoroughly(simulationGame);
                        for (let i = 0; i < nextPositions.length; i++) {
                            const nextPosition = nextPositions[i];
                            move = [[nextPosition.row, nextPosition.col], null, null];
                            childNode = new MNode(move, currentNode, uctConst);
                            currentNode.addChild(childNode);
                        }
                        if (simulationGame.pawnOfTurn.numberOfLeftWalls > 0) {
                            // heuristic:
                            // if opponent has no walls left,
                            // place walls only to interrupt the opponent's path,
                            // not to support my pawn.
                            const noBlockNextWallsInterupt =
                                simulationGame.getArrOfValidNoBlockNextWallsDisturbPathOf(simulationGame.pawnOfNotTurn);
                            const noBlockNextHorizontalsInterupt = noBlockNextWallsInterupt.arrOfHorizontal;
                            for (let i = 0; i < noBlockNextHorizontalsInterupt.length; i++) {
                                move = [null, noBlockNextHorizontalsInterupt[i], null];
                                childNode = new MNode(move, currentNode, uctConst);
                                currentNode.addChild(childNode);
                            }
                            const noBlockNextVerticalsInterupt = noBlockNextWallsInterupt.arrOfVertical;
                            for (let i = 0; i < noBlockNextVerticalsInterupt.length; i++) {
                                move = [null, null, noBlockNextVerticalsInterupt[i]];
                                childNode = new MNode(move, currentNode, uctConst);
                                currentNode.addChild(childNode);
                            }
                        }
                    }
                    this.rollout(randomChoice(currentNode.children));
                    currentNode = this.root;
                }
            }
            else {
                currentNode = currentNode.maxUCTChild;
            }
        }
    }
}*/


MonteCarlo::MonteCarlo(int id, int depth, long time)
{
    mSelfID = id;
    mThinkDepth = depth;
    mTimeLimited = time;
    isAIRunning = false;
}

