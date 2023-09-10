def bfs(graph, start, goal):
    visited = []
    # queue = [(start)]
    queue = [('', start)]
    while queue:
        path, vertex = queue.pop(0)
        print(f"path : {path}, vertex : {vertex}")
        # vertex = queue.pop(0)
        # print(vertex)
        if vertex == goal:
            return path
        if vertex not in visited:
            visited.append(vertex)
            for neighbor in graph[vertex]:
                if neighbor not in visited:
                    queue.append((path + '->' + neighbor,neighbor))
                    # queue.append((neighbor))
    return None

graph = {
    'A': ['B', 'C', 'D'],
    'B': ['A', 'E', 'F'],
    'C': ['A', 'G', 'H', 'K'],
    'D': ['A', 'I'],
    'E': ['B', 'X'],
    'F': ['B', 'L', 'G'],
    'G': ['F', 'M', 'C'],
    'H' : ['C', 'N'],
    'K': ['C', 'I'],
    'I':['D', 'K', 'N'],
    'X': ['E', 'L'],
    'L':['F', 'X', 'V', 'M'],
    'M':['G','L','T'],
    'N':['H', 'Z', 'I'],
    'V':['L'],
    'T':['M'], 
    'Z':['N']

    # 0:[1,2],
    # 1:[2],
    # 2:[0, 3],
    # 3:[3]
}

start_vertex = 'C'
goal_vertex = 'V'

path = bfs(graph, start_vertex, goal_vertex )
if path:
    print("path from", start_vertex, "to", goal_vertex, ":", path)
else:
    print("Cant find", start_vertex, "to", goal_vertex)
