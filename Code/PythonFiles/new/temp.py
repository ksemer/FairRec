""" For adhock puproses.
"""
import subprocess
subprocess.call(['cp ~/Workspace/FairRec/Code/PythonFiles/new/fairRec.py .'], cwd= ".", shell= True)
import fairRec as fr
import sys 
import pickle

# Calculate initial pagerank.
print('Get pagerank...')
try:
    fileOne = open('out_pagerank.txt', 'r')
    fileOne.close()
    print('Pagerank already calculated.')
except:
    print("Pagerank calculation...")
    subprocess.call(['cp ~/Workspace/FairRec/Code/CppFiles/getPagerank.out .'], cwd= ".", shell= True)
    subprocess.call(['./getPagerank.out'], cwd= ".", shell= True)

# Calculate red absorbing probs.
print('Take Red absorbing probs...')
try:
    fileOne = open('out_personilized_red.txt', 'r')
    fileOne.close()
    print('Reb absorbing probs already calculated.')
except:
    print("Red absorbing probs calculation...")
    subprocess.call(['cp ~/Workspace/FairRec/Code/CppFiles/absorbingProbs.out .'], cwd= ".", shell= True)
    subprocess.call(['./absorbingProbs.out -r'], cwd= ".", shell= True)

# Get classifier.
print('Get node2vec classifier...')
try:
    node2vecRecommender = pickle.load(open('edgeClassifier.sav', 'rb') )
    print('Classifier already exists.')
except:
    print('Train classifier...')
    fr.trainModel(False)

# Get Node embeddings.
print('Get node embeddings...')
try:
    fileOne = open('out_nodeEmbeddings.txt', 'r')
    fileOne.close()
    print('Node embeddings already exists.')
except:
    print('Calculate node embeddings...')
    subprocess.call(['cp ~/Workspace/snap/examples/node2vec/node2vec .'], cwd= ".", shell= True)
    subprocess.call(['./node2vec -i:out_graph.edgelist -o:out_nodeEmbeddings.txt -l:3 -d:128 -p:0.3 -dr -v'], cwd= ".", shell= True)

# Get source nodes.
print('Get source nodes...')
try:
    fileOne = open('randomSourceNodes.txt', 'r')
    fileOne.close()
    fileOne = open('redBestSourceNodes.txt', 'r')
    fileOne.close()
    fileOne = open('blueBestSourceNodes.txt', 'r')
    fileOne.close()
    print('Source nodes already calculated')
except:
    print('Get source nodes...')
    subprocess.call(['cp ~/Workspace/FairRec/Code/CppFiles/getSourceNodes.out .'], cwd= ".", shell= True)
    subprocess.call(['./getSourceNodes.out'], cwd= ".", shell= True)

# Get edge fairness score.
print('Get edge fairness scores...')
try:
    fileOne = open('randomSourceNodes.txt', 'r')
    fileOne.readline()
    testNode = int(fileOne.readline() )
    fileOne.close()
    fileOne = open('%dedgeFairnessScores.txt' %testNode, 'r')
    fileOne.close()
    print('Edge fairnes scores already calculated.')
except:
    print('Get edge fairness scores...')
    subprocess.call(['cp ~/Workspace/FairRec/Code/CppFiles/getEdgeFairnessScore.out .'], cwd= ".", shell= True)
    subprocess.call(['./getEdgeFairnessScore.out'], cwd= ".", shell= True)


# if it needs get candidate edges.
fileOne = open('out_graph.txt', 'r')
numberOfNodes = int(fileOne.readline() )
fileOne.close()
if numberOfNodes > 35000:
    pass
    # Get candidate edges.

# Get edge scores.
print('Get Edge Scores...')
try:
    fileOne = open('edgeRecScores.txt', 'r')
    fileOne.close()
    print('Edge scores already calculated.')
except:
    print('Get edge scores...')
    subprocess.call(['cp ~/Workspace/FairRec/Code/PythonFiles/new/getEdgesScores.py .'], cwd= ".", shell= True)
    subprocess.call(['python3 getEdgesScores.py'], cwd= ".", shell= True)