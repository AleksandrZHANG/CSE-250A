import numpy as np
import sys

def read_prob(filename):
	action = np.zeros((81, 81), dtype = float)
	for line in open(filename):
		line = line.split()
		action[int(line[0]) - 1, int(line[1]) - 1] = float(line[2])
	return action
			
def read_rewards(filename):
	rewards = np.zeros((81, 1), dtype = int)
	i = 0
	for line in open(filename):
		rewards[i][0] = int(line)
		i += 1
	return rewards

#find the value for action	
def update(action, state, vk):
	max_value = -sys.maxsize
	max_action = 0
	for i in range(4):
		temp = 0.0
		for j in range(81):
			temp += action[i][state][j] * vk[j]
		if temp > max_value:
			max_value = temp
			max_action = i
	return max_value, max_action

#get the transition matrix for action
def transition_matrix(action, pi):
	transition = np.zeros((81, 81), dtype = float)
	for i in range(81):
		transition[i] = action[pi[i]][i]
	return transition

def partb(action, v, rewards):
	pi = [0] * 81
	for iter in range(2000):
		v = list(v)
		for i in range(81):
			max_value, max_action = update(action, i, v)
			pi[i] = max_action
			v[i] = rewards[i][0] + 0.9875 * max_value
	return pi, v

def policy_iteration(action, v, rewards):
	pi = [0] * 81
	identity_matrix = np.zeros((81, 81), dtype = int)
	for i in range(81):
		identity_matrix[i][i] = 1 
	for iter in range(5):
		v = np.matrix(identity_matrix - 0.9875 * transition_matrix(action, pi)).I * rewards
		for i in range(81):
			max_value, max_action = update(action, i, v)
			pi[i] = max_action
			v[i] = rewards[i][0] + 0.9875 * max_value	
	return pi, v
	
v = [0.0] * 81
rewards = read_rewards('C:/rewards.txt')
action1 = read_prob('C:/prob_a1.txt')	
action2 = read_prob('C:/prob_a2.txt')
action3 = read_prob('C:/prob_a3.txt')
action4 = read_prob('C:/prob_a4.txt')
action = [action1, action2, action3, action4]

#part a and b
res, value = partb(action, v, rewards)
print (res)
print (value)

#part c
policy_iteration, value = policy_iteration(action, v, rewards)
print (policy_iteration)
print (value)
