/* QtIRC - Qt based IRC client
 * Copyright (C) 2012-2015 Jacob Dawid (jacob@omg-it.works)
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as
 * published by the Free Software Foundation, either version 3 of the
 * License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 */

#pragma once

/**
  * \namespace IRCError
  * This namespace includes all numeric IRC errors.
  */
namespace IRCError {
const int NoSuchNick = 401;
const int NoSuchServer = 402;
const int NoSuchChannel = 403;
const int CannotSendToChannel = 404;
const int TooManyChannels = 405;
const int WasNoSuchNick = 406;
const int TooManyTargets = 407;
const int NoSuchService = 408;
const int NoOrigin = 409;
const int NoRecipient = 411;
const int NoTextToSend = 412;
const int NoTopLevel = 413;
const int WildTopLevel = 414;
const int BasMask = 415;
const int UnknownCommand = 421;
const int NoMessageOfTheDay = 422;
const int NoAdminInfo = 423;
const int FileError = 424;
const int NoNickNameGiven = 431;
const int ErroneusNick = 432;
const int NicknameInUse = 433;
const int NickCollision = 436;
const int UnavailResource = 437;
const int UserNotInChannel = 441;
const int NotOnChannel = 442;
const int UserOnChannel = 443;
const int NoLogin = 444;
const int SummonDisabled = 445;
const int UsersDisabled = 446;
const int NotRegistered = 451;
const int NeedMoreParams = 461;
const int AlreadyRegistered = 462;
const int NoPermissionForHost = 463;
const int PasswordMismatch = 464;
const int YouAreBannedCreep = 465;
const int YouWillBeBanned = 466;
const int KeySet = 467;
const int ChannelIsFull = 471;
const int UnknownMode = 472;
const int InviteOnlyChannel = 473;
const int BannedFromChannel = 474;
const int BadChannelKey = 475;
const int BadChannelMask = 476;
const int NoChannelModes = 477;
const int BanListFull = 478;
const int NoPrivileges = 481;
const int ChannelOperatorPrivilegesNeeded = 482;
const int CannotKillServer = 483;
const int Restricted = 484;
const int UniqueOperatorPrivilegesNeeded = 485;
const int NoOperatorHost = 491;
const int YourModeListUnknownFlag = 501;
const int UsersDontMatch = 502;
}
