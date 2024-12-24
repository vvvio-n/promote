import gym
import numpy as np
from matplotlib import pyplot as plt


env = gym.make('CartPole-v1')
env.reset()

# 打印游戏
def show():
    plt.imshow(env.render(mode = 'rgb_array'))
    plt.show()

show()

#测试游戏环境
def test_env():
    state = env.reset()
    print('state=',state)

    action = env.action_space.sample()
    print('action=',action)

    # 假设 action 是你选择的动作
    state, reward, over, _ = env.step(action)

    print('state=', state)
    print('reward=', reward)
    print('over=', over)

test_env()

import torch

# 动作模型
model = torch.nn.Sequential(
    torch.nn.Linear(4,128),
    torch.nn.ReLU(),
    torch.nn.Linear(128,2),
)

# 经验模型
next_model = torch.nn.Sequential(
    torch.nn.Linear(4, 128),
    torch.nn.ReLU(),
    torch.nn.Linear(128, 2),
)

# 把model的参数给next_model
next_model.load_state_dict(model.state_dict())

print(model,next_model)
# 输入状态，输出评分

import random

def get_action(state):
    if random.random()<0.01:
        return random.choice([0, 1])
    state = torch.FloatTensor(state).reshape(1, 4)
    return model(state).argmax().item()

get_action([0.01320812,  0.2083405,  -0.01109628, -0.342673])

#样本池
datas = []

def update_data():
    old_count = len(datas)

    while len(datas) - old_count < 200:
        state = env.reset()

        over = False
        while not over:
            action = get_action(state)
            next_state, reward, over , _ = env.step(action)

            datas.append((state, action, reward, next_state, over))

        state = next_state

    update_count = len(datas) - old_count
    drop_count = max(len(datas)-10000,0)
    while len(datas)>10000:
        datas.pop(0)

    return update_count, drop_count
update_count, drop_count = update_data()
print(update_count, drop_count, len(datas))

# 获取样本
def get_sample():
    sample = random.sample(datas, 64)
    state = torch.FloatTensor(np.array([i[0] for i in sample])).reshape(-1, 4)
    action = torch.LongTensor(np.array([i[1] for i in sample])).reshape(-1, 1)
    reward = torch.FloatTensor(np.array([i[2] for i in sample])).reshape(-1, 1)
    next_state = torch.FloatTensor(np.array([i[3] for i in sample])).reshape(-1, 4)
    over = torch.FloatTensor(np.array([i[4] for i in sample])).reshape(-1, 1)
    return state, action,next_state, over, reward
state, action,next_state, over,reward = get_sample()
print(state, action, next_state, over, reward)

def get_value(state, action):
    value = model(state)
    value = value.gather(dim=1, index=action)
    return value
result = get_value(state, action)
print("Result shape:", result.shape)

def get_target(reward, next_state, over):
    with torch.no_grad():
         target = next_model(next_state)
    target = target.max(dim=1)[0]
    target = target.reshape(-1,1)
    target *= 0.98
    target *= (1 - over)
    target += reward
    return target

#  print(get_target(reward, next_state, over).shape)

from IPython import display

def test(play):
    state = env.reset()
    reward_sum = 0
    over = False
    while not over:
        action = get_action(state)
        state, reward, over, info = env.step(action)
        reward_sum += reward

        if play and random.random()<0.2:
            display.clear_output(wait = True)
            show()
    return reward_sum

def train():
    model.train()
    optimizer = torch.optim.Adam(model.parameters(), lr=2e-3)
    loss_fn = torch.nn.MSELoss()

    for epoch in range(500):
        update_count, drop_count = update_data()
        for i in range(200):
            state, action, reward, next_state, over = get_sample()
            value = get_value(state,action)
            target = get_target(reward, next_state, over)
            loss = loss_fn(value, target)
            optimizer.zero_grad()
            loss.backward()
            optimizer.step()
            if(i + 1) % 10 == 0:
                next_model.load_state_dict(model.state_dict())

        if epoch % 50 == 0:
            test_result = sum([test(play=False)for _ in range(20)])/20
            print('score=', test_result)
# print(train())

print(test(play = True))
