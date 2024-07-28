# 简单使用

1. 定义切片slice

```js
src/store/user.js
import { createSlice } from "@reduxjs/toolkit";
const userSlice = createSlice({
	name: "user",
	initialState: {
		name: "张三",
		gender: "男",
		age: 18,
	},
	reducers: { // 这里的reducer都是同步的
		setName(state, action) {
			state.name = action.payload;
		},
	},
});

export const { setName } = userSlice.actions;
export default userSlice;
```

2. 在另外文件夹中定义store

```js
/src/store/index.js
import { configureStore } from "@reduxjs/toolkit";
import userSlice from "./user";

export const store = configureStore({
	reducer: {
		user: userSlice.reducer,
	},
});
```

3. 使用Provider包裹App根组件

```js
/main.jsx
import React from 'react'
import ReactDOM from 'react-dom/client'
import App from './App.jsx'
import './index.css'
import { store } from './store/index.js'
import {Provider} from 'react-redux'

ReactDOM.createRoot(document.getElementById('root')).render(
  <React.StrictMode>
    <Provider store={store}>
    <App />
    </Provider>
  </React.StrictMode>,
)
```

4. 使用数据

```js
/src/Pages/
import {useDispatch, useSelector} from 'react-redux';
import {setName} from '../store/user';
export const User = () => {
    const userStore = useSelector((state) => state.user); // state.user对应的是第二部中store.reducer的键名
    const dispatch = useDispatch();
    return <>
        <div>{JSON.stringify(userStore)}</div>
        <button onClick={() => {
            dispatch(setName('李四'));
        }}>点击</button>
    </>
}
```

5. 定义异步方法

```js
/src/store/user.js
export const mock_Api = () => { // 模拟API
	return new Promise((resolve) => {
		setTimeout(() => {
			resolve({
				data: {
					name: "mock_Api" + Math.random().toFixed(2) * 100,
					age: Math.random().toFixed(2) * 100,
				},
			});
		}, 500);
	});
};
//1. 定义异步trunk,使用就是使用这个
export const mockUserQuery = createAsyncThunk("user/UserQuery", async () => {
	return await mock_Api();
});
//2. 在slice内部使用extraReducers
const userSlice = createSlice({
	name: "user",
	initialState: {
		name: "张三",
		gender: "男",
		age: 18,
	},
	reducers: {
		setName(state, action) {
			state.name = action.payload;
		},
	},
	extraReducers: (builder) => {
		builder.addCase(mockUserQuery.fulfilled, (state, action) => {
			state.name = action.payload.data.name;
			state.age = action.payload.data.age;
		});
	},
});

export const { setName } = userSlice.actions;
export default userSlice;
```

6. 使用异步方法

```js
/src/Pages/user.jsx
import {useDispatch, useSelector} from 'react-redux';
import {mockUserQuery, setName} from '../store/user';
export const User = () => {
    const userStore = useSelector((state) => state.user);
    const dispatch = useDispatch();
    return <>
        <div>{JSON.stringify(userStore)}</div>
        <button onClick={() => {
            dispatch(mockUserQuery());
        }}>异步点击</button>
    </>
}
```

7. 一些ts的简化

```ts
src/store/index.ts
import { configureStore } from "@reduxjs/toolkit";
import {TypedUseSelectorHook, useDispatch, useSelector} from "react-redux";
import userSlice from "./user";

export const store = configureStore({
	reducer: {
		user: userSlice.reducer,
	},
});

export type RootState = ReturnType<typeof store.getState>;
export type RootDispatch = typeof store.dispatch;

export const useAppSelector:TypedUseSelectorHook<RootState> = useSelector;
export const useAppDispatch = () => useDispatch<RootDispatch>();

```

