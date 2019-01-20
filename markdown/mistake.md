# Mistake

## Bfs

1. emm...                                                   (0)
1. Forget to pop-up the element in queue in BFS.            (2)
1. Push node-u into the queue instead of node-v in BFS.     (1)

## Dfs

1. emm...                                                   (0)
1. Forget to record where the node come from, which may causes
  endless loop.                                             (0)

## Dinic

1. emm...                                                   (0)
1. Use the edge whose capacity is zero.                     (2)
1. Push node-s into the queue instead of node-v in BFS.     (1)
1. Forget to copy head[] after each BFS.                    (1)
1. Forget to use Current Arc Optimization.                  (1)
1. After dinic, not realize cap[] is chaned.                (1)

## Bipartite graph

1. emm...                                                   (0)
1. Add edge x1-y1(in the same side) instead of x1-y2.       (1)
1. Add directed edge instead of undirected.                 (1)

## Chain forword star

1. emm...                                                   (0)
1. While adding x-y, set to[x] instead of to[p].            (1)

## Hungrian

1. emm...                                                   (0)
1. After arriving a matched node, fotget to pass the matched
  edge but to search each edge linked to the node
  incorrectly.                                              (1)
1. Forget to record whether a node is in current path.      (0)

## Other

1. emm...                                                   (0)
1. Use memset(a, 0, sizeof(**0**)) incorrectly.             (1)
1. After backuping a array, forget to copy it back.         (1)


